#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <poll.h>
#include <errno.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 10
#define CLIENT_SIZE 96

typedef struct {
  int fd;
  char bufer[BUF_SIZE];
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

  if (-1 == bind(listen_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) {
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
  int listen_fd = create_socket(atoi(argv[2]));


    return 0;
}


