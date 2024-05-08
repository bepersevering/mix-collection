#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <strings.h>

#define SERV_PORT 9909
#define	MAXLINE		4096

void dg_echo(int, struct sockaddr *, socklen_t);

int main(int argc, char **argv) {
  int sockfd;

  struct sockaddr_in servaddr, cliaddr;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd == -1) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  bzero(&servaddr, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(SERV_PORT);

  if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  dg_echo(sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr));

}

void dg_echo(int sockfd, struct sockaddr *cliaddr, socklen_t clilen) {
  int n;
  socklen_t len;

  char mesg[MAXLINE];

  for (;;) {
    len = clilen; 

    n = recvfrom(sockfd, mesg, MAXLINE, 0, cliaddr, &len);
    if (n < 0) {
      perror("recvfrom failed");
      continue;
    }


    sendto(sockfd, mesg, n, 0, cliaddr, len);
  }

}
