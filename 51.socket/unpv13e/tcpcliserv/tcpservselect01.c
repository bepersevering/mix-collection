#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <strings.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>
#include <signal.h>


#define MAXLINE 4096
#define LISTENQ 1024
#define SERV_PORT 9909
#define SERV_IP "127.0.0.1"
#define INF 1000000000
#define N 100000
#define M 100000
int main(int argc, char **argv) {
  int i, maxi, maxfd, listenfd, connfd, sockfd;

  int nready, client[FD_SETSIZE];

  ssize_t n;
  fd_set rset, allset;
  char buf[MAXLINE];
  socklen_t clilen;

  struct sockaddr_in cliaddr, servaddr;
  // socket
  listenfd = socket(AF_INET, SOCK_STREAM, 0);

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(SERV_PORT);

  // bind
  bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

  // listen
  listen(listenfd, LISTENQ);

  maxfd = listenfd;
  maxi = -1;
  for (i = 0; i < FD_SETSIZE; i++) {
    client[i] = -1;
  }

  FD_ZERO(&allset);
  FD_SET(listenfd, &allset);

  for (;;) {
    rset = allset; /* structure assignment*/
    nready = select(maxfd + 1, &rset, NULL, NULL, NULL);

    if (FD_ISSET(listenfd, &rset)) {
      // new client connection
      connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
      for (i = 0; i < FD_SETSIZE; i++) {
        
      }
    }
  }

}