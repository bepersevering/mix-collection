#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>

#define PORT 9090
#define BUF_SIZE 1024
#define MAX_CLIENTS 100



int main() {
  int sock_fd, client_sock, max_fd, activity, i, sd;
  struct sockaddr_in server_addr;
  fd_set readfds;

  int client_sockets[MAX_CLIENTS] = {0};
  int addr_len = sizeof(server_addr);

  // create server socket
  sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd == 0) {
    perror("socket() error");
    exit(EXIT_FAILURE);
  }

  // bind port
  server_addr.sin_family = AF_INET;




}
