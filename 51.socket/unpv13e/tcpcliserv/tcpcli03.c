#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <error.h>
#include <unistd.h>
#include <math.h>

#define SERV_PORT 9011
#define LISTENQ 1024
#define MAXLINE 4096

int max(int a, int b){
  return a > b ? a: b;
}

void
str_cli(FILE *fp, int sockfd);

int main(int argc, char **argv) {
  int sockfd;
  struct sockaddr_in servaddr;

  if (argc != 2) {
    perror("usage tcpcli <IPaddress>\n");
    exit(1);
  };

  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  bzero(&servaddr, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(SERV_PORT);
  servaddr.sin_addr.s_addr = htonl(atoi(argv[1]));

  connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

  str_cli(stdin, sockfd);

  exit(0);
}

void
str_cli(FILE *fp, int sockfd) {
  int maxfd1, stdineof;
  fd_set rset;

  char buf[MAXLINE];
  int n;

  stdineof = 0;

  FD_ZERO(&rset);
  for (;;) {
    if (stdineof == 0) {
      FD_SET(fileno(fp), &rset);
    }
    FD_SET(sockfd, &rset);
    maxfd1 = max(fileno(fp), sockfd) + 1;
    select(maxfd1, &rset, NULL, NULL, NULL);

    if (FD_ISSET(sockfd, &rset)) {
      // socket is readable
      if ((n = read(sockfd, buf, MAXLINE)) == 0) {
        if (stdineof == 1) {
          return;
        } else {
          perror("str_cli: server terminated permaturely");
          exit(1);
        }
      }
      write(fileno(stdout), buf, n);
    }

    if (FD_ISSET(fileno(fp), &rset)) {
      // input is readable
      if ((n == read(fileno(fp), buf, MAXLINE)) == 0) {
        stdineof = 1;
        // send FIN
        shutdown(sockfd, SHUT_WR);
        FD_CLR(fileno(fp), &rset);
        continue;
      }
      write(sockfd, buf, n);
    }

  
  }  

}

// void
// str_cli(FILE *fp, int sockfd) {
//   char sendline[MAXLINE], recvline[MAXLINE];

//   while (fgets(sendline, MAXLINE, fp) != NULL) {
//     write(sockfd, sendline, strlen(sendline));

//     if (read(sockfd, recvline, MAXLINE) == 0) {
//       fprintf(2, "str_cli: server terminated prematurely");
//       exit(1);
//     }

//     fputs(recvline, stdout);
//   }
  
// }
