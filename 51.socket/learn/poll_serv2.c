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

int createSocket(int port) {
  int listen_fd = -1;
  struct sockaddr_in servaddr;

  if (-1 == (listen_fd = socket(PF_INET, SOCK_STREAM, 0))) {
    fprintf(stderr, "create socket error: %d, %s\n", errno, strerror(errno));
    exit(1);
  }

  int reuseaddr = 1;
  if (-1 == (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, 
      &reuseaddr, sizeof(reuseaddr)))) {
    fprintf(stderr, "setsockopt error: %d, %s\n", errno, strerror(errno));
    exit(1);
  }
  
  bzero(&servaddr, sizeof(servaddr));

  servaddr.sin_family = PF_INET;
  servaddr.sin_port = htons(port);

  inet_pton(PF_INET, "0.0.0.0", &servaddr.sin_addr);

  if (-1 == bind(listen_fd, (struct sockaddr *)&servaddr, sizeof(servaddr))) {
    fprintf(stderr, "bind error: %d, %s\n", errno, strerror(errno));
    exit(1);
  }

  if (-1 == listen(listen_fd, 5)){
    fprintf(stderr, "listen: %d, %s\n", errno, strerror(errno));
    exit(1);
  }

  return listen_fd;
}
