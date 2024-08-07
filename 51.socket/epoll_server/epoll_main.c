#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "epoll_http.h"

int main(int argc, char **argv) {
  if (argc < 3) {
    printf("eg: ./epoll_main.out port path\n");
    exit(1);
  }

  // 端口
  int port = atoi(argv[1]);
  // 修改进行的工作目录，方便后续操作
  int ret = chdir(argv[2]);
  
  if (ret == -1) {
    perror("chdir error");
    exit(1);
  }

  // 启动epoll模型
  epoll_run(port);

  return 0; 
}
