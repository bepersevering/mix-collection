#include <asm-generic/errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <strings.h>
#include <poll.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>


#define INFTIM          (-1)    /* infinite poll timeout */
#define MAXLINE 4096
#define LISTENQ 1024
#define SERV_PORT 9909
#define SERV_IP "127.0.0.1"
#define INF 1000000000
#define N 100000
#define M 100000
#define OPEN_MAX 4096

int main(int argc, char **argv) {
  int i, maxi, listenfd, connfd, sockfd;
  int nready;
  ssize_t n;
  char buf[MAXLINE];

  socklen_t clilen;
  struct pollfd client[OPEN_MAX]; 
  struct sockaddr_in cliaddr, servaddr;

  listenfd = socket(AF_INET, 
                        SOCK_STREAM, 0);

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_port = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(SERV_PORT);

  bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
  
  listen(listenfd, LISTENQ);

  client[0].fd = listenfd;
  client[0].events = POLLRDNORM;
  
  for (i = 1; i < OPEN_MAX; i++) {
    client[i].fd = -1;  // -1 indicates available entry
  }

  // max index into client[] array
  maxi = 0;

  for (;;) {
    nready = poll(client, maxi + 1, INFTIM);

    if (client[0].revents & POLLRDNORM) {
      // new client connection
      clilen = sizeof(cliaddr);
      connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);

      for (i = 1; i < OPEN_MAX; i++) {
        if (client[i].fd < 0) {
          client[i].fd = connfd;    // save descriptor
          break;
        }

        if (i == OPEN_MAX) {
          perror("too many clients");
          exit(1);
        }
        
        client[i].events = POLLRDNORM;
        if (i > maxi) {
          // max index in client[] array
          maxi = i;
        }
        
        if (--nready <= 0) {
          // no more readable descriptors
          continue;
        }
      }

      for (i = 1; i < maxi; i++) {
        // check all clients for data
        if ((sockfd = client[i].fd) < 0) {
          continue;
        }

        if (client[i].revents & (POLLRDNORM | POLLERR)) {
          if ((n = read(sockfd, buf, MAXLINE)) < 0) {
            if (errno == ECONNRESET) {
              // connection reset by client
              close(sockfd);
              client[i].fd = -1;
            } else {
              perror("read error");
            }
          } else if (n == 0) {
            // connection closed by client
            close(sockfd);
            client[i].fd = -1;
          } else {
            write(sockfd, buf, n);
          }

          if (--nready <= 0) {
            break;
          }
        }
      }
    }
  }

}
