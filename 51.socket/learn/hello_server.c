#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char **argv) {
  int serv_sock;
  int cli_sock;

  struct sockaddr_in serv_addr;
  struct sockaddr_in cli_addr;

  socklen_t clilen;

  char message[] = "Hello World!";

  if (argc != 2) {
    printf("Usage: %s <port>\n", argv[0]);
    exit(1);
  }

  serv_sock = socket(PF_INET, SOCK_STREAM, 0);
  if (serv_sock == -1) {
    error_handling("socket() error");
  }

  bzero(&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(atoi(argv[1]));

  if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
    error_handling("bind() error");
  }

  if (listen(serv_sock, 5) == -1) {
    error_handling("listen() error");
  }

  clilen = sizeof(cli_addr);

  cli_sock = accept(serv_sock, (struct sockaddr *)&cli_addr, &clilen);
  if (cli_sock == -1) {
    error_handling("accept() error");
  }

  write(cli_sock, message, sizeof(message));
  close(cli_sock);
  close(serv_sock);
  
  return 0;
}


void error_handling(char *message) {
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}
