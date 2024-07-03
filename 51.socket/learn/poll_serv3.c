#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 10
#define CLIENT_SIZE 96

typedef struct {
  int fd;
  char buffer[BUF_SIZE];
} ClientData;

int create_socket(int port) {
  struct sockaddr_in serv_addr;
  int listen_fd = -1;
  if (-1 == (listen_fd = socket(PF_INET, SOCK_STREAM, 0))) {
    fprintf(stderr, "create socket() error: %d, %s\n", errno, strerror(errno));
    exit(1);
  }

  bzero(&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);
  inet_pton(PF_INET, "0.0.0.0", &serv_addr.sin_addr);

  if (-1 == bind(listen_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))) {
    fprintf(stderr, "bind() error: %d, %s\n", errno, strerror(errno));
    exit(1);
  }

  if (-1 == listen(listen_fd, 5)) {
    fprintf(stderr, "listen() %d, %s\n", errno, strerror(errno));
    exit(1);
  }
  return listen_fd;
}

int set_no_block(int fd) {
  int old_opt = fcntl(fd, F_GETFL);
  int new_opt = old_opt | O_NONBLOCK;
  fcntl(fd, F_SETFL, new_opt);
  return old_opt;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage %s <port> \n", argv[1]);
    exit(1);
  }

  struct pollfd fds[CLIENT_SIZE];
  ClientData clientData[CLIENT_SIZE]; 
  int listen_fd = create_socket(atoi(argv[1]));
  fds[0].fd = listen_fd;
  fds[0].events = POLLIN | POLLERR;
  fds[0].revents = 0;
  int conn_count = 0;

  for (int i = 0; i < CLIENT_SIZE; i++) {
    clientData[i].fd = -1;
  }

  while(1) {
    int ret = poll(fds, conn_count+1, -1);
    if (ret < 0) {
      fprintf(stderr, "poll: %d, %s\n", errno, strerror(errno));
      exit(1);
    }

    for (int i = 0; i < conn_count + 1; i++) {
      // 如果是POLLRDHUP 或者POLLERR
      if ((fds[i].revents & POLLHUP) || (fds[i].revents & POLLERR)) {
        int fd = fds[i].fd;
        fds[i] = fds[conn_count];
        clientData[i] = clientData[conn_count];
        i--;
        conn_count--;
        close(fd);
        printf("delete connection: %d\n", fd);
      }
      else if ((fds[i].fd == listen_fd) && (fds[i].revents & POLLIN)) {
        // 如果fd是监听fd且为POLLIN事件
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        int client_fd = -1;
        if (-1 == (client_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &client_len))) {
          fprintf(stderr, "accept: %d, %s\n", errno, strerror(errno));
          exit(1);
        }

        printf("get connection %d from %s:%d\n", 
               client_fd, inet_ntoa(client_addr.sin_addr), client_addr.sin_port);

        conn_count++;
        set_no_block(client_fd);
        fds[conn_count].fd = client_fd;
        // 设置关心的事件
        fds[conn_count].events = POLLIN | POLLHUP | POLLERR;
        fds[conn_count].revents = 0;
        clientData[conn_count].fd = client_fd;
      }
      else if (fds[i].revents & POLLIN) {
        // 有可读数据
        char buf[BUF_SIZE] = {0};

        int recv_len = recv(fds[i].fd, buf, BUF_SIZE - 1, 0);

        if (recv_len > 0) {
          strncpy(clientData[i].buffer, buf, BUF_SIZE - 1);
          fds[i].events = fds[i].events & (~POLLIN);
          fds[i].events = fds[i].events | POLLOUT;
        } else if (recv_len == 0) {
          printf("---------client %d exit(not print) ----------\n", fds[i].fd);
        } else {
          fprintf(stderr, "recv: %d, %s\n", errno, strerror(errno));
          exit(1);
        }
      } else if (fds[i].revents & POLLOUT) {
        // 写数据
        if (send(fds[i].fd, clientData[i].buffer, 
          strlen(clientData[i].buffer), 0) < 0) {
          
          if (ECONNRESET == errno) {
            continue;
          }
          fprintf(stderr, "send: %d, %s\n", errno, strerror(errno));
          exit(1);
        }
        fds[i].events &= (~POLLOUT);
        fds[i].events |= POLLIN;

      }

    }
  }

  return 0;
}
