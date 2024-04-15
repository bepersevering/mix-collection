#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <strings.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <error.h>
#include <unistd.h>
#include <math.h>
#include <signal.h>

#define SERV_PORT 9011
#define LISTENQ 1024
#define MAXLINE 4096


void str_echo(int connfd);

int max(int a, int b){
  return a > b ? a: b;
}

int main(int argc, char **argv) {
  int listenfd, connfd;
  pid_t childpid;
  socklen_t clilen;
  struct sockaddr_in cliaddr, servaddr;

  // create socket fd
  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  if (listenfd < 0) {
    perror("socket error");
    exit(EXIT_FAILURE);
  }

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  // 网络传输用的大端序
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(SERV_PORT);

  // bind socket fd
  if(bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
    perror("bind error");
    exit(EXIT_FAILURE);
  }

  // listen fd
  if (listen(listenfd, LISTENQ) < 0) {
    perror("listen error");
    exit(EXIT_FAILURE);
  }

  // 处理僵尸进程
  signal(SIGCHLD, SIG_IGN);

  for(;;) {
    clilen = sizeof(cliaddr);
    connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);

    if (connfd < 0) {
      perror("accept error");
      exit(EXIT_FAILURE);
    }

    if ((childpid = fork()) == 0) {
      // 关闭监听套接字
      close(listenfd);
      // 处理客户端请求
      str_echo(connfd);
      // 子进程结束
      exit(EXIT_SUCCESS);
    }

    // 父进程关闭已连接套接字
    close(connfd);
  }

}

void str_echo(int sockfd) {

}
