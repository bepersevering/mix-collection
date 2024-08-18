#include "select_http.h"
#include <arpa/inet.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_CLIENTS 200
#define BUFFER_SIZE 1024


int init_listen_fd(int port) {
  int listen_fd;

  struct sockaddr_in serv_addr;

  listen_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (listen_fd < 0) {
    perror("socket error");
    exit(EXIT_FAILURE);
  }

  bzero(&serv_addr, sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(listen_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
    perror("bind error");
    exit(EXIT_FAILURE);
  }
  
  if (listen(listen_fd, LISTENQ) < 0) {
    perror("listen error");
    exit(EXIT_FAILURE);
  }

  return listen_fd;
}



// select run
void select_run(int port) {
  int listen_fd, max_fd, client_fd;
  fd_set allset, readset;

  int client[FD_SETSIZE];
  int nready;

  struct sockaddr_in client_addr;

  socklen_t cli_len;
  int i;

  listen_fd = init_listen_fd(port);
  max_fd = listen_fd;
  
  for (i = 0; i < FD_SETSIZE; i++) {
    client[i] = -1;
  }

  FD_ZERO(&allset);

  FD_SET(listen_fd, &allset);

  // 循环
  while (1) {
    readset = allset; 
    
    // select
    nready = select(max_fd + 1, &readset, NULL, NULL, NULL);

    if (FD_ISSET(listen_fd, &readset)) {
      // 有可读事件

    }


  }






}
