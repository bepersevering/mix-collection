#include "select_http.h"
#include <arpa/inet.h>
#include <ctype.h>
#include <dirent.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_CLIENTS 200
#define BUFFER_SIZE 1024



// select run
void select_run(int port) {
  int socket_fd, client_fd, max_sd, activity, new_socket;
  struct sockaddr_in server_addr;
  int addr_len = sizeof(server_addr);
  int client_sockets[MAX_CLIENTS];
  fd_set readfds;

  int socket_opt = 1;
  // 创建socket
  socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd == 0) {
    perror("socket failed\n");
    exit(EXIT_FAILURE);
  }
  // 允许重用端口和地址
  if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &socket_opt,
                 sizeof(socket_opt)) < 0) {
    perror("setsockopt failed\n");
    exit(EXIT_FAILURE);
  }

  // 设置socket的地址和端口号
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  // bind
  if (bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
      0) {
    perror("bind failed\n");
    exit(EXIT_FAILURE);
  }

  // listen
  if (listen(socket_fd, 5) < 0) {
    perror("listen failed\n");
    exit(EXIT_FAILURE);
  }

  printf("Server start, listening on port %d ...\n", port);

  // 循环处理
  while (1) {
    // clear the socket set
    FD_ZERO(&readfds);

    // add server socket to set
    FD_SET(socket_fd, &readfds);

    max_sd = socket_fd;

    // add child sockets to set
    for (i = 0; i < MAX_CLIENTS; i++) {
      sd = client_sockets[i];

      // 
    }

  }
}
