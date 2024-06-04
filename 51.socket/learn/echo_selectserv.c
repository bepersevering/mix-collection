#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>

#define BUF_SIZE 128
void error_handling(char *msg);

int main(int argc, char **argv) {
  int serv_sock, client_sock;
  struct sockaddr_in servaddr, cliaddr;
  struct timeval timeout;
  fd_set reads, cpy_reads;

  socklen_t addrsize;
  int fd_max, str_len, fd_num, i;
  char buf[BUF_SIZE];

  if (argc != 2) {
    printf("Usage : %s <port>\n", argv[0]);
    exit(1);
  }

  serv_sock = socket(PF_INET, SOCK_STREAM, 0);
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(atoi(argv[1]));

  if (bind(serv_sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
    error_handling("bind() error");
  }

  if (listen(serv_sock, 5) == -1) {
    error_handling("listen() error");
  }

  FD_ZERO(&reads);
  FD_SET(serv_sock, &reads);

  fd_max = serv_sock;

  while (1) {
    cpy_reads = reads;
    timeout.tv_sec = 5;
    timeout.tv_usec = 5000;

    if ((fd_num = select(fd_max + 1, &cpy_reads, 0, 0, &timeout)) == -1) {
      break;
    }
    if (fd_num == 0) {
      continue;
    }
    for (i = 0; i < fd_max + 1; i++) {
      if (FD_ISSET(i, &cpy_reads)) {
        if (i == serv_sock) {
          addrsize = sizeof(cliaddr);
          client_sock =
              accept(serv_sock, (struct sockaddr *)&cliaddr, &addrsize);

          FD_SET(client_sock, &reads);
          if (fd_max < client_sock) {
            fd_max = client_sock;
            printf("connected client: %d\n", client_sock);
          } else {
            str_len = read(i, buf, BUF_SIZE);
            if (str_len == 0) {
              // close request
              FD_CLR(i, &reads);
              close(i);
              printf("close client : %d\n", i);
            } else {
              write(i, buf, str_len);
            }
          }
        }
      }
    }
  }
  close(serv_sock);

  return 0;
}

void error_handling(char *msg) {
  fputs(msg, stderr);
  fputc('\n', stderr);
  exit(1);
}
