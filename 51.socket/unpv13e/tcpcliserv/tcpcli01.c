#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERV_PORT 8099
#define MAXLINE 4096
#define LISTENQ 1024

void str_cli(FILE *fp, int sockfd);

int main(int argc, char **argv) {
  int sockfd;
  struct sockaddr_in servaddr;

  if (argc != 2) {
    perror("usage tcp cli <IPaddress>\n");
  }
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  bzero(&servaddr, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(SERV_PORT);

  inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
  connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
  str_cli(stdin, sockfd);
  exit(0);
}

void str_cli(FILE *fp, int sockfd) {
  char sendline[MAXLINE], recvline[MAXLINE];
  while(fgets(sendline, MAXLINE, fp) != NULL) {
    write(sockfd, sendline, sizeof(sendline));
  
    if (read(sockfd, recvline, MAXLINE) == 0) {
      perror("str_cli: server terminated permaturely");
    }
    fputs(recvline, stdout);
  }
}
