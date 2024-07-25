#include "epoll_http.h"
#include <arpa/inet.h>
#include <ctype.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_SIZE 2000

void epoll_run(int port) {
  // 创建一个epoll树的根节点
  int epoll_fd = epoll_create(MAX_SIZE);
  if (-1 == epoll_fd) {
    perror("epoll_create error");
    exit(1);
  }

  // 添加要监听的节点
  // 先添加监听listen_fd
  int listen_fd = init_listen_fd(port, epoll_fd);
  // 委托内核检测添加到树上的节点
  struct epoll_event all_events[MAX_SIZE];

  while (1) {
    int ret = epoll_wait(epoll_fd, all_events, MAX_SIZE, -1);
    if (-1 == ret) {
      perror("epoll_wait error");
      exit(1);
    }

    // 遍历发生变化的节点
    int i = 0;
    for (i = 0; i < ret; i++) {
      // 只处理读事件，其他事件默认不处理
      struct epoll_event *pev = &all_events;
      if (!(pev->events & EPOLLIN)) {
        // 不是读事件
        continue;
      }

      if (pev->data.fd == listen_fd) {
        // 接受连接请求
        do_accept(listen_fd, epoll_fd);
      } else {
        // 读数据
        do_read(pev->data.fd, epoll_fd);
      }
    }
  }
}

/**
 * 读数据
 */
void do_read(int client_fd, int epoll_fd) {
  // 将浏览器发过来的数据，读到buf中
  char line[1024] = {0};
  // 读请求行
  int len = get_line(client_fd, line, sizeof(line));

  if (0 == len) {
    printf("client disconnect...\n");
    // 关闭套接字，client_fd从epoll上del
    disconnect(client_fd, epoll_fd);
  } else {
    printf("request data: %s", line);
    printf("============= request header ============\n");
    // 还有数据没读完
    // 继续读
    while (len) {
      char buf[1024] = {0};
      len = get_line(client_fd, buf, sizeof(buf));
      printf("-----: %s", buf);
    }
    printf("============= The End ============\n");
  }

  // 请求行：get /xxx http/1.1
  // 判断是汪是get请求
  if (strncasecmp("get", line, 3) == 0) {
    // 处理http请求
    http_request(line, client_fd);
    // 关闭套接字，client_fd从epoll上del
    disconnect(client_fd, epoll_fd);
  }
}


// 断开连接的函数
void disconnect(int client_fd, int epoll_fd) {
  int ret = epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client_fd, NULL);
  if (ret == -1) {
    perror("epoll_ctl_del cfd erro");
    exit(1);
  }
  close(client_fd);
}

// 处理http请求
void http_request(const char *request, int client_fd) {
  // 拆分http请求行
  // get /xxx http/1.1
  char method[12], path[1024], protocol[12];

  sscanf(request, "%[^ ] %[^ ] %[^ ]", method, path, protocol);
  printf("method = %s, path = %s, protocal = %s\n", method, path, protocol);

  // 转码 将不能识别的中文乱码 --> 中文
  // 解码 %23 %34 %5f
  decode_str(path, path);
  // 处理path  /xx
  // 去掉path中的/
  char* file = path + 1;
  // 如果没有指定访问的资源，默认显示资源目录中的内容
  if (strcmp(path, "/") == 0) {
    // file的值，资源目录的当前位置
    file = "./";
  }

  // 获取文件属性


}



int main(int argc, char **argv) { return 0; }
