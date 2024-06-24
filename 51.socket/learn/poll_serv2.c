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

int createSocket() {
  int listen_fd = -1;
  struct sockaddr_in servaddr;

  if (-1 == (listen_fd = socket(PF_INET, SOCK_STREAM, 0))) {

  }
}
