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
  if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) {
    
  }

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
        if (client[i] < 0) {
          // save descriptor
          client[i] =  connfd;
          break;
        }

        if (i == FD_SETSIZE) {
          perror("too many clients");
          exit(1);
        }

        // add new descriptor to set
        FD_SET(connfd, &allset);
        if (connfd > maxfd) {
          // for select
          maxfd = connfd;
        }

        if (i > maxi) {
          // max index in client[] array
          maxi = i;
        }
      }

      for (i = 0; i < maxi; i++) {
        // check all clients for data
        if ((sockfd = client[i]) < 0) {
          continue;
        }

        if (FD_ISSET(sockfd, &rset)) {
          if ((n = read(sockfd, buf, MAXLINE)) == 0) {
            // connection closed by client
            close(sockfd);
            FD_CLR(sockfd, &allset);
            client[i] = -1;
          } else {
            write(sockfd, buf, n);
          }

          if (--nready <= 0) {
            // no more readable descriptor
            break;
          }
        }
      }
    }
  }

}