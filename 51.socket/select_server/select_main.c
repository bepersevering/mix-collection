#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include "select_http.h"


int main(int argc, char** argv) {
  if (argc != 3) {
    printf("Usage <port> <resource_path>\n");
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

  // 启动select模型
  select_run(port);

  return 0;
}
