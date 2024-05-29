#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *msg);
void read_routine(int sock, char *buf);
void write_routine(int sock, char *buf);


int main(int argc, char **argv) {

  int sockfd;
  char msg[BUF_SIZE];
  pid_t pid;
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
  } 

  pid = fork();

  if(pid == 0) {
    // child process
    write_routine(sockfd, msg);
  } else {
    read_routine(sockfd, msg);
  }

  close(sockfd);
  return 0;
}

void read_routine(int sockfd, char *buf) {
  while(1) {
    int str_len = read(sockfd, buf, BUF_SIZE);

    if (str_len == 0) {
      return;
    }

    buf[str_len] = 0;
    printf("Message from server: %s\n", buf);
  }
}

void write_routine(int sockfd, char *buf) {
  while(1) {
    fgets(buf, BUF_SIZE, stdin);

    if (!strcmp(buf, "q\n") || !strcmp(buf, "Q\n")) {
      shutdown(sockfd, SHUT_WR);
      return;
    }

    write(sockfd, buf, strlen(buf));
  }
}

void error_handling(char *msg) {
  fputs(msg, stderr);
  fputc('\n', stderr);
  exit(1);
}
