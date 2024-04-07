#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <error.h>
#include <unistd.h>

#define SERV_PORT 9011
#define LISTENQ 1024
#define MAXLINE 4096

void
str_cli(FILE *fp, int sockfd);

int main(int argc, char **argv[]) {
  int sockfd;
  struct sockaddr_in servaddr;

  if (argc != 2) {
    fprintf(2, "usage tcpcli <IPaddress>\n");
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
  char sendline[MAXLINE], recvline[MAXLINE];

  while (fgets(sendline, MAXLINE, fp) != NULL) {
    write(sockfd, sendline, strlen(sendline));

    if (read(sockfd, recvline, MAXLINE) == 0) {
      fprintf(2, "str_cli: server terminated prematurely");
      exit(1);
    }

    fputs(recvline, stdout);
  }
  
}
