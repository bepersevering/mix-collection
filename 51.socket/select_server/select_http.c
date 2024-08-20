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

  if (bind(listen_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
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
      cli_len = sizeof(client_addr);
      client_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &cli_len);

      if (client_fd < 0) {
        perror("accept error");
        continue;
      }

      // 将client_fd放到client未使用的里面
      for (i = 0; i < FD_SETSIZE; i++) {
        if (client[i] < 0) {
          client[i] = client_fd;
          break;
        }
      }

      // 客户端数量已经达到最大值,FD_SETSIZE
      if (i == FD_SETSIZE) {
        fprintf(stderr, "too many clients\n");
        continue;
      }

      FD_SET(client_fd, &allset);

      if (max_fd < client_fd) {
        max_fd = client_fd;
      }

      if (--nready <= 0) {
        continue;
      }
    }

    for (i = 0; i <= max_fd; i++) {
      if (client[i] < 0) {
        continue;
      }
      // 可读
      if (FD_ISSET(client[i], &readset)) {
        do_read(client_fd);
        break;
      }
    }
  }
}

void do_accept(int listen_fd) {
  struct sockaddr_in client_addr;
  socklen_t client_len = sizeof(client_addr);

  int client_fd =
      accept(listen_fd, (struct sockaddr *)&client_addr, &client_len);
  if (client_fd < 0) {
    perror("accept error");
    exit(EXIT_FAILURE);
  }

  do_read(client_fd);
}

void do_read(int client_fd) {
  char buf[BUFFER_SIZE];

  int n = get_line(client_fd, buf, sizeof(buf));

  if (n <= 0) {
    disconnect(client_fd);
  } else {
    http_request(buf, client_fd);
  }
}

int get_line(int sock_fd, char *buf, int size) {
  int i = 0;
  char c = '\0';
  int n;

  while ((i < size - 1) && c != '\n') {
    n = recv(sock_fd, &c, 1, 0);
    if (n > 0) {
      if (c == '\r') {
        n = recv(sock_fd, &c, 1, MSG_PEEK);
        if ((n > 0) && (c == '\n')) {
          recv(sock_fd, &c, 1, 0);
        } else {
          c = '\n';
        }
      }
      buf[i] = c;
      i++;
    } else {
      c = '\n';
    }
  }
  buf[i] = '\0';

  return i;
}

void disconnect(int client_fd) { close(client_fd); }

// handle http request
void http_request(const char *request, int client_fd) {
  char method[12], path[1024], port[12];

  scanf(request, "%[^ ] %[^ ] %[^ ]", method, path, port);

  // 判断是不是GET请求
  if (strcasecmp(method, "GET") != 0) {
    send_respond_head(client_fd, 501, "Not Support", "text/html", -1);
    return;
  }

  char *file_path = path + 1;
  struct stat st;

  if (stat(file_path, &st) == -1) {
    send_respond_head(client_fd, 404, "Not Found", "text/html", -1);
    return;
  } else {
    if (S_ISDIR(st.st_mode)) {
      // 目录
      send_dir(client_fd, file_path);
    } else {
      // 文件
      send_file(client_fd, file_path);
    }
  }
}

void send_respond_head(int client_fd, int status, char *desp, char *type,
                       long length) {
  char buf[MAX_CLIENTS];

  sprintf(buf, "HTTP/1.1 %d %s\r\n", status, desp);
  send(client_fd, buf, strlen(buf), 0);

  sprintf(buf, "Content-Type  %s\r\n", type);
  send(client_fd, buf, strlen(buf), 0);

  sprintf(buf, "Content-Length %ld\r\n", length);
  send(client_fd, buf, strlen(buf), 0);

  sprintf(buf, "\r\n");
  send(client_fd, buf, strlen(buf), 0);
}

// send file
void send_file(int client_fd, const char *filename) {
  int file_fd = open(filename, O_RDONLY);

  if (-1 == file_fd) {
    send_respond_head(client_fd, 404, "Not Found", "text/html", -1);
    exit(EXIT_FAILURE);
  }

  char buf[4096];

  int ret = 0;
  while ((ret = read(file_fd, buf, sizeof(buf))) > 0) {
    send(client_fd, buf, ret, 0);
  }

  if (-1 == ret) {
    perror("read error");
    exit(EXIT_FAILURE);
  }
  close(client_fd);
}

// send dir
void send_dir(int client_fd, const char *dirname) {
  char file[1024] = {0};
  char buf[4096] = {0};

  sprintf(buf, "<html><head>目录名:%s</head></html>", dirname);
  sprintf(buf + strlen(buf), "<body><h1>当前目录：%s</h1></body>", dirname);

#if 1
  DIR *dir = opendir(dirname);
  struct dirent *ptr = NULL;
  while((ptr = readdir(dir)) != NULL) {
    char *filename = ptr->d_name;

    // 拼接文件的完整路径
    sprintf(file, "%s/%s", dirname, filename);
  }  

#endif
}
