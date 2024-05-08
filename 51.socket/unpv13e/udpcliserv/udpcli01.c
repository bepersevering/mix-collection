#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <strings.h>
#include <string.h>
#include <arpa/inet.h>



#define SERV_PORT 9909
#define	MAXLINE		4096


void dg_cli(FILE *, int, struct sockaddr *, socklen_t);

int main(int argc, char **argv) {
  int sockfd;

  struct sockaddr_in servaddr;

  if (argc != 2) {
    perror("usage: udpcli01 <IPaddress>");
    exit(EXIT_FAILURE);
  }

  bzero(&servaddr, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(SERV_PORT);

  if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
    perror("inet_pton error");
    exit(EXIT_FAILURE);
  }

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd == -1) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  dg_cli(stdin, sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

  exit(0);
  
}

void dg_cli(FILE *fp, int sockfd, struct sockaddr * servaddr, socklen_t servlen) {
  int n;
  char sendline[MAXLINE], recvline[MAXLINE + 1];

  while(fgets(sendline, MAXLINE, fp) != NULL) {
    sendto(sockfd, sendline, strlen(sendline), 0, servaddr, servlen);

    n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
    if (n <= 0) {
      perror("recvfrom failed");
      continue;
    }

    // null terminate
    recvline[n] = '\0';    

    fputs(recvline, stdout);
  }
}
