#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 1024

void error_handling(char *msg);

int main(int argc, char **argv) {
  int serv_sock, client_sock;
  FILE *readfp;
  FILE *writefp;

  struct sockaddr_in servaddr, clientaddr;

  socklen_t cli_addr_size;
  char buf[BUF_SIZE] = {
      0,
  };
  bzero(&servaddr, sizeof(servaddr));

  servaddr.sin_family = PF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(atoi(argv[1]));

  serv_sock = socket(AF_INET, SOCK_STREAM, 0);

  if (serv_sock == -1) {
    error_handling("socket() error");
  }

  if ((bind(serv_sock, (struct sockaddr*)&servaddr, sizeof(servaddr))) == -1) {
    error_handling("bind() error");
  }

  listen(serv_sock, 5);

  cli_addr_size = sizeof(clientaddr);
  client_sock = accept(serv_sock, (struct sockaddr *)&clientaddr, &cli_addr_size);

  readfp = fdopen(client_sock, "r");
  writefp = fdopen(client_sock, "w");

  fputs("FROM SERVER: Hi~ client? \n", writefp);
  fputs("I love all of the world \n", writefp);
  fputs("You are awesome! \n", writefp);

  fflush(writefp);
  fclose(writefp);

  fgets(buf, sizeof(buf), readfp);
  fputs(buf, stdout);
  fclose(readfp);
  return 0;
}

void error_handling(char *msg) {
  fputs(msg, stderr);
  fputc('\n', stderr);
  exit(1);
}
