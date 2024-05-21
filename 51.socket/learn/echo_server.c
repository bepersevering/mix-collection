#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *msg);

int main(int argc, char **argv) {
  int serv_sock, client_sock;
  char msg[BUF_SIZE];
  int str_len, i;

  struct sockaddr_in servaddr, cliaddr;

  socklen_t clilen;

  if (argc != 2) {
    printf("Usage: %s <port> \n", argv[0]);
    exit(1);
  }

  serv_sock = socket(PF_INET, SOCK_STREAM, 0);
  if (serv_sock == -1) {
    error_handling("socket() error");
  }

  bzero(&servaddr, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr  = htonl(INADDR_ANY);
  servaddr.sin_port = htons(atoi(argv[1]));

  if (bind(serv_sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
    error_handling("bind() error");
  }

  if (listen(serv_sock, 5) == -1) {
    error_handling("listen() error");
  }
  
  clilen = sizeof(cliaddr);

}
