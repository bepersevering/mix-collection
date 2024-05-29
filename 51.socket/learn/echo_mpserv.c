#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/socket.h>


#define BUF_SIZE 30
void error_handling(char *msg);
void read_childproc(int sig);

int main(int argc, char **argv) {
  int serv_sock, cli_sock;

  struct sockaddr_in serv_addr, cli_addr;

  pid_t pid;

  struct sigaction act;

  socklen_t addr_size;
  int str_len, state;

  char buf[BUF_SIZE];

  if (argc != 2) {
    printf("Usage: %s <port>\n", argv[0]);
    exit(1);
  }

  act.sa_handler = read_childproc;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;
  state = sigaction(SIGCHLD, &act, 0);

  serv_sock = socket(PF_INET, SOCK_STREAM, 0);

  bzero(&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(atoi(argv[1]));

  // bind
  if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
    // 分配IP 地址和端口
    error_handling("bind() error");
  }

  if (listen(serv_sock, 5) == -1) {
    error_handling("listen() error");
  } 


  while(1) {
    addr_size = sizeof(cli_addr);

    cli_sock = accept(serv_sock, (struct sockaddr *)&cli_addr, &addr_size);

    if (cli_sock == -1) {
      continue;
    } else {
      puts("new client connected...");
    }

    pid = fork();

    if (pid == -1) {
      close(cli_sock);
      continue;
    }
    if (pid == 0) {
      close(serv_sock);
      while ((str_len = read(cli_sock, buf, BUF_SIZE)) != 0) {
        write(cli_sock, buf, str_len);
      }
      close(cli_sock);
      puts("client disconnected...");
      return 0;
    } else {
      close(cli_sock);
    }
  }

  close(serv_sock);

}


void error_handling(char *msg) {
  fputs(msg, stderr);
  fputc('\n', stderr);
  exit(1);;;;
}


void read_childproc(int sig) {
  pid_t pid;
  int status;
  pid = waitpid(-1, &status, WNOHANG);
  printf("remove process id: %d\n", pid);
}
