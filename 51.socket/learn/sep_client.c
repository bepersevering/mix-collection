#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

int main(int argc, char **argv) {
  int sockfd;
  char buf[BUF_SIZE];
  struct sockaddr_in serv_addr;

  FILE *readfp;
  FILE *writefp;

  sockfd = socket(PF_INET, SOCK_STREAM, 0);
  bzero(&serv_addr, sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
  serv_addr.sin_port = htons(atoi(argv[2]));

  connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
  readfp = fdopen(sockfd, "r");
  writefp = fdopen(sockfd, "w");

  while (1) {
    if (fgets(buf, sizeof(buf), readfp) == NULL) {
      break;
    }
    fputs(buf, stdout);
    fflush(stdout);
  }

  fputs("FROM CLIENT: Thank you! \n", writefp);
  fflush(writefp);
  fclose(writefp);
  fclose(readfp);
  return 0;
}
