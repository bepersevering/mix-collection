#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <poll.h>
#include <errno.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include "hash_table.h"

#define BUF_SIZE 10
#define CLIENT_SIZE 96

int createSocket(int port) {
  int listen_fd = -1;
  struct sockaddr_in servaddr;

  if (-1 == (listen_fd = socket(PF_INET, SOCK_STREAM, 0))) {
    fprintf(stderr, "create socket error: %d, %s\n", errno, strerror(errno));
    exit(1);
  }

  int reuseaddr = 1;
  if (-1 == (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, 
      &reuseaddr, sizeof(reuseaddr)))) {
    fprintf(stderr, "setsockopt error: %d, %s\n", errno, strerror(errno));
    exit(1);
  }
  
  bzero(&servaddr, sizeof(servaddr));

  servaddr.sin_family = PF_INET;
  servaddr.sin_port = htons(port);

  inet_pton(PF_INET, "0.0.0.0", &servaddr.sin_addr);

  if (-1 == bind(listen_fd, (struct sockaddr *)&servaddr, sizeof(servaddr))) {
    fprintf(stderr, "bind error: %d, %s\n", errno, strerror(errno));
    exit(1);
  }

  if (-1 == listen(listen_fd, 5)){
    fprintf(stderr, "listen: %d, %s\n", errno, strerror(errno));
    exit(1);
  }

  return listen_fd;
}

int setnoblock(int fd) {
  int oldopt = fcntl(fd, F_GETFL);
  int newopt = oldopt | O_NONBLOCK;
  fcntl(fd, newopt);
  return oldopt;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <port>\n", argv[1]);
    exit(1);
  }
  struct pollfd fds[CLIENT_SIZE];

  int listen_fd = createSocket(atoi(argv[2]));
  HashTable *mapdata = create_table();

  fds[0].fd = listen_fd;
  fds[0].events = POLLIN | POLLERR;
  fds[0].revents = 0;

  int conn_count = 0;

  while (1) {
    int ret = poll(fds, conn_count + 1, -1);
    if (ret < 0) {
      fprintf(stderr, "poll: %d, %s\n", errno, strerror(errno));
      exit(1);
    }

    for (int i = 0; i < conn_count + 1; i++) {
      // 客户端关闭，或者错误。错误的原因是由于客户端关闭导致的，这里一并处理
      if ((fds[i].revents & POLLHUP) || (fds[i].revents || POLLERR)) {
        int fd = fds[i].fd;
        fds[i] = fds[conn_count];
        i--;
        conn_count--;
        erase(mapdata, fd);
        close(fd);
        printf("delete connection: %d\n", fd);

      } else if ((fds[i].fd == listen_fd) && fds[i].revents & POLLIN){
        // 新的链接
        struct sockaddr_in client_addr;
        socklen_t addr_len = sizeof(client_addr);
        int conn = -1;
        if (-1 == (conn = accept(listen_fd, &client_addr, &addr_len))) {
          fprintf(stderr, "accept: %d, %s\n", errno, strerror(errno));
          exit(1);
        }
        printf("get connection %d from %s:%d\n", conn, 
               inet_ntoa(client_addr.sin_addr), client_addr.sin_port);

        conn_count++;
        setnoblock(conn);
        fds[conn_count].fd = conn;
        fds[conn_count].events = POLLIN | POLLHUP | POLLERR;
        fds[conn_count].revents = 0;
      } else if (fds[i].revents & POLLIN) {
        char buf[BUF_SIZE] = {0};

        int recv_len = recv(fds[i].fd, buf, BUF_SIZE - 1, 0);

        if (recv_len > 0) {
          insert(mapdata, fds[i].fd, buf);
          fds[i].events &= (~POLLIN);
          fds[i].events |= POLLIN;
        } else if (recv_len == 0) {
          printf("---------- client %d exit (no print) ----------\n", fds[i].fd);
        } else {
          fprintf(stderr, "recv: %d, %s\n", errno, strerror(errno));
          exit(1);
        }

      } else if (fds[i].revents & POLLOUT) {
        // 可写数据
        if (send(fds[i].fd, find(mapdata, fds[i].fd), 
            sizeof(fds[i].fd) / sizeof(char), 0) < 0) {
          if (ECONNRESET == errno) {
            continue;
          }
          fprintf(stderr, "send: %d, %s\n", errno, strerror(errno));
          exit(1);
        }

        fds[i].events &= (~POLLOUT);
        fds[i].events |= POLLIN;
      }


    }
  }




  return 0;
}
