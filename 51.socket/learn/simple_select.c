#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <unistd.h>

#define PORT 9090
#define BUF_SIZE 1024
#define MAX_CLIENTS 100

void handle_client(int client_sock) {
  
}

int main() {
  int sock_fd, client_sock, max_fd, activity, i, sd;
  struct sockaddr_in server_addr, client_addr;
  fd_set readfds;

  int client_sockets[MAX_CLIENTS] = {0};
  int addr_len = sizeof(server_addr);

  // create server socket
  sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd == 0) {
    perror("socket() error");
    exit(EXIT_FAILURE);
  }

  // bind to the port
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    perror("bind failed");
    close(sock_fd);
    exit(EXIT_FAILURE);
  }

  // listen for incoming connections
  if (listen(sock_fd, 5) < 0) {
    perror("listen error");
    close(sock_fd);
    exit(EXIT_FAILURE);
  }

  printf("Listening on port %d...\n", PORT);

  while (1) {
    // clear the socket set
    FD_ZERO(&readfds);

    // add server socket to set
    FD_SET(sock_fd, &readfds);

    max_fd = sock_fd;

    // add child sockets to set
    for (i = 0; i < MAX_CLIENTS; i++) {
      sd = client_sockets[i];

      // if valid socket descriptor then add to read list
      if (sd > 0) {
        FD_SET(sd, &readfds);
      }

      // update max_fd for select function
      if (sd > max_fd) {
        max_fd = sd;
      }
    }

    // wait for activity on one of the sockets

    activity = select(max_fd + 1, &readfds, NULL, NULL, NULL);

    if((activity < 0) && (errno != EINTR)) {
      perror("select error");
      exit(EXIT_FAILURE);
    }


    // if something happened on the server socket, then it's an incoming connection 
    if (FD_ISSET(sock_fd, &readfds)) {
      if ((client_sock == accept(sock_fd, (struct sockaddr *)&client_addr, (socklen_t *)&addr_len)) < 0) {
        perror("accept error");
        exit(EXIT_FAILURE);
      }

      printf("New connection, socket fd is %d, ip is %s, port: %d\n",
             client_sock, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port)
             );

      // add new socket to array of sockets
      for (i = 0; i < MAX_CLIENTS; i++) {
        if (client_sockets[i] == 0) {
          client_sockets[i] = client_sock;
          printf("adding to list of sockets as %d\n", i);
          break;
        }
      }

    }
    // handle IO operation on some other socket
    for (i = 0; i < MAX_CLIENTS; i++) {
      sd = client_sockets[i];

      if (FD_ISSET(sd, &readfds)) {
        // handle client request
        handle_client(sd);
        client_sockets[i] = 0;
      }
    }

  }

  return 0;
}
