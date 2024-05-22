#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *msg);


int main(int argc, char **argv) {

  int sockfd;
  char msg[BUF_SIZE];
  int str_len, recv_len, recv_cnt;
  struct sockaddr_in servaddr;

  if (argc != 3) {
    printf("Usage: %s <IP> <port>\n", argv[0]);
    exit(1);
  }

  sockfd = socket(PF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    error_handling("socket() error");
  }

  bzero(&servaddr, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr(argv[1]);
  servaddr.sin_port = htons(atoi(argv[2]));

  if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
    error_handling("connect() error");
  } else {
    puts("Connected ......");
  }

  while(1) {
    fputs("Input message(Q to quit):", stdout);
    fgets(msg, BUF_SIZE, stdin);

    if (!strcmp(msg, "q\n") || !strcmp(msg, "Q\n")) {
      break;
    }

    str_len = write(sockfd, msg, strlen(msg));

    recv_len = 0;
    while (recv_len < str_len) {
      recv_cnt = read(sockfd, &msg[recv_len], BUF_SIZE - 1);
      if (recv_cnt == -1) {
        error_handling("read() error!");
      }
      recv_len += recv_cnt;
    }
    msg[recv_len] = 0;
    printf("Message from server: %s", msg);
  }

  close(sockfd);
  return 0;
}

void error_handling(char *msg) {
  fputs(msg, stderr);
  fputc('\n', stderr);
  exit(1);
}
