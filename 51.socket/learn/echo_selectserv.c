#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>

#define BUF_SIZE 128
void error_handling(char *msg);

int main(int argc, char **argv) {
  int serv_sock, client_sock;
  struct sockaddr_in servaddr, cliaddr;
  struct timeval timeout;
  fd_set reads, cpy_reads;

  socklen_t addrsize;
  int fd_max, str_len, fd_num, i;

  if (argc !=2) {
    printf("Usage : %s\n", argv[0]);
    exit(1);
  }

  serv_sock = socket(PF_INET, SOCK_STREAM, 0);
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(atoi(argv[1]));

  if (bind(serv_sock, (struct sockaddr *)&serv_sock, sizeof(servaddr)) == -1) {
    error_handling("bind() error");
  }

  if (listen(serv_sock, 5) == -1) {
    error_handling("listen() error");
  }

  FD_ZERO(&reads);
  FD_SET(serv_sock, &reads);

  fd_max = serv_sock;

  while(1) {
    cpy_reads = reads;
    timeout.tv_sec = 5;
    timeout.tv_usec = 5000;

    fi ((fd_num = select(fd_max + 1, &cpy_reads, 0, 0, &timeout)) == -1) {
      break;
    }




  }



}
