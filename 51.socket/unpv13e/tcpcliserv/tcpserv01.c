#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

#define SERV_PORT 8099
#define MAXLINE 4096

#define handle_error(msg) \
  do {perror(msg); exit(EXIT_FAILURE);} while(0)

void str_echo(int connfd) {
  // read from connfd
  size_t n;
  char buf[MAXLINE];
again:
  while((n = read(connfd, buf, MAXLINE)) > 0) {
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

  if ((listenfd = socket(AF_INET, SOCK_STREAM, 0) == -1)) {
    handle_error("socket");
  } 
  
  bzero(&servaddr, 0);

  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(SERV_PORT);

  if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
    handle_error("bind");
  }

  listen(listenfd, 5);

  for (;;) {
    clilen = sizeof(cliaddr);
    connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
    if (connfd == -1) {
      handle_error("accept");
    }

    if ((childpid = fork()) == 0) {
      // child process
      close(listenfd);
      str_echo(connfd);
      exit(0);
    } else {
      close(connfd);
    }

  }

}
