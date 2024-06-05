#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 30
void error_handling(char *msg);

int main(int argc, char **argv) {
  int sockfd;
  struct sockaddr_in sockaddr;
  if (argc != 3) {
    printf("Usage: %s <IP> <port>\n", argv[0]);
    exit(1);
  }

  sockfd = socket(PF_INET, SOCK_STREAM, 0);
  bzero(&sockaddr, sizeof(sockaddr));

  sockaddr.sin_family = AF_INET;
  sockaddr.sin_addr.s_addr = inet_addr(argv[1]);
  sockaddr.sin_port = htons(atoi(argv[2]));

  if (connect(sockfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) == -1) {
    error_handling("connect() error");
  }

  write(sockfd, "123", strlen("123"));
  send(sockfd, "4", strlen("4"), MSG_OOB);
  write(sockfd, "567", strlen("567"));
  send(sockfd, "890", strlen("890"), MSG_OOB);

  close(sockfd);
  return 0;
}

void error_handling(char *msg) {
  fputs(msg, stderr);
  fputc('\n', stderr);
  exit(1);
}
