#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>


void error_handling(char *msg);


int main(int argc, char **argv) {
  int sockfd;
  struct sockaddr_in send_addr;
  char *msg = "123";
  if (argc != 3) {
    printf("Usage: %s <IP> <port>\n", argv[0]);
    exit(1);
  }

  sockfd = socket(PF_INET, SOCK_STREAM, 0);
  bzero(&send_addr, sizeof(send_addr));
  send_addr.sin_family = AF_INET;
  send_addr.sin_addr.s_addr = inet_addr(argv[1]);
  send_addr.sin_port = htons(atoi(argv[2]));

  if (connect(sockfd, (struct sockaddr *)&send_addr, sizeof(send_addr)) == -1) {
    error_handling("connect() error");
  }

  write(sockfd, msg, strlen(msg));

  close(sockfd);
  return 0;
}

void error_handling(char *msg) {
  fputs(msg, stderr);
  fputc('\n', stderr);
  exit(1);
}

