#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>

#define SERV_PORT 9099
#define MAXLINE 4096
#define LISTENQ 1024

#define handle_error(msg)                                                      \
  do {                                                                         \
    perror(msg);                                                               \
    exit(EXIT_FAILURE);                                                        \
  } while (0)

void str_echo(int connfd) {
  // read from connfd
  size_t n;
  char buf[MAXLINE];
again:
  while ((n = read(connfd, buf, MAXLINE)) > 0) {
    write(connfd, buf, n);
  }
  if (n < 0 && errno == EINTR) {
    goto again;
  } else {
    handle_error("str_echo: read error");
  }
}

int main(int argc, char **argv) {
  int listenfd, connfd;
  pid_t childpid;
  socklen_t clilen;
  struct sockaddr_in cliaddr, servaddr;

  listenfd = socket(AF_INET, SOCK_STREAM, 0);

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(SERV_PORT);

  bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

  listen(listenfd, LISTENQ);

  for (;;) {
    clilen = sizeof(cliaddr);
    connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
    if ((childpid == fork()) == 0) {
      // child process
      close(listenfd);
      str_echo(connfd);
      exit(0);
    }
    close(connfd);
  }

  exit(0);
}
