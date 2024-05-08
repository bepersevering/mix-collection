#include <stdio.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>

#define SERV_PORT 9909

void dg_echo(int sockfd, struct sockaddr *cliaddr, int addr_len);

int main(int argc, char **argv) {
  int sockfd;

  struct sockaddr_in servaddr, cliaddr;

  sockfd = sockfd(AF_INET, SOCK_DGRAM, 0);

  bzero(&servaddr);

  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(SERV_PORT);

  bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

  dg_echo(sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr));

}

void dg_echo(int sockfd, struct sockaddr *cliaddr, int addr_len) {

}
