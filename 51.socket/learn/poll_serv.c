#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

// 定义socket可排队个数
#define BACKLOG 10

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

int socket_server_init(char *listen_ip, int listen_port);

int main(int argc, char **argv) {
  int listen_fd = -1;
  int client_fd = -1;
  int rv = -1;
  int listen_port = 0;
  int max = 0;
  struct pollfd fds_array[1024];
  int i, j;
  int found;
  char buf[1024];

  // 用来确认程序执行的格式是否正确，不正确则退出并提醒用户
  if (argc < 2) {
    printf("Usage: %s <port>\n", argv[0]);
    return -1;
  }

  // 将端口参数赋值给变更
  // 由于命名行传参数进来是字符串类型，所以需要atoi转换为整型
  listen_port = atoi(argv[1]);

  // 创建listen_fd，这里封闭了一个函数
  if ((listen_fd = socket_server_init(NULL, listen_port)) < 0) {
    printf("server listen on port[%d] failure: %s\n", listen_port,
           strerror(errno));
    return -2;
  }

  // 将数组中每个元素都设置为-1，相当于清空fd
  for (int i = 0; i < ARRAY_SIZE(fds_array); i++) {
    fds_array[i].fd = -1;
  }

  // 将listen_fd和期待POLLIN存入结构体数据中第0个元素中
  fds_array[0].fd = listen_fd;
  fds_array[0].events = POLLIN;

  // 当前结构体中，最大的下标是0
  max = 0;

  while (1) {
  }
}
