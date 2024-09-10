#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 6369
#define BUFFER_SIZE 1024

void print_menu() {
  printf("Avaliable commands:\n");
  printf("1. SET <key> <value>\n");
  printf("2. SET <key> <value>\n");
  printf("3. DELETE <key>\n");
  printf("4. EXIT\n");
}

int main(int argc, char **argv) {
  int sockfd;
  struct sockaddr_in server_addr;
  char send_buf[BUFFER_SIZE];
  char recv_buf[BUFFER_SIZE];
  char command[BUFFER_SIZE], key[BUFFER_SIZE], value[BUFFER_SIZE];

  // create client socket
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  // config addr
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);

  // connection to server
  if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
    perror("Invalid address/ Address not supported");
    close(sockfd);
    exit(EXIT_FAILURE);
  }

  // connect server
  if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
      0) {
    perror("connect failed");
    close(sockfd);
    exit(EXIT_FAILURE);
  }

  printf("Connected to Redis server on port %d\n", PORT);
  print_menu();

  // 交互
  while (1) {
    printf("redis-cli>");
    if (fgets(send_buf, sizeof(send_buf), stdin) == NULL) {
      printf("\n");
      break;
    }
    // 去掉换行
    send_buf[strcspn(send_buf, "\n")] = '\0';
    // 解析命令
    int argc = sscanf(send_buf, "%s %s %s", command, key, value);
    if (argc <= 0) {
      printf("Please enter a command.\n");
      continue;
    }

    if (strcasecmp(command, "SET") == 0) {
      // set k,v
      if (argc != 3) {
        printf("Usage: SET <key><value>\n");
        continue;
      }
      // 构建命令字符串
      snprintf(send_buf, sizeof(send_buf), "SET %s %s\n", key, value);
    } else if (strcasecmp(command, "GET") == 0) {
      // get k
      if (argc != 2) {
        printf("Usage: GET <key>\n");
        continue;
      }
      // 构建命令字符串
      snprintf(send_buf, sizeof(send_buf), "GET %s\n", key);
    } else if (strcasecmp(command, "DELETE") == 0) {
      // delete k
      if (argc != 2) {
        printf("Usage: DELETE <key>\n");
        continue;
      }
      // 构建命令字符串
      snprintf(send_buf, sizeof(send_buf), "DELETE %s\n", key);
    } else if (strcasecmp(command, "EXIT") == 0) {
      break;
    } else {
      printf("Unknown command. Please use SET, GET, DELETE, EXIT.\n");
      continue;
    }

    // 发送命令到服务器
    if (send(sockfd, send_buf, sizeof(send_buf), 0) < 0) {
      perror("send failed");
      break;
    }

    // 接收响应
    memset(recv_buf, 0, sizeof(recv_buf));

    ssize_t n = recv(sockfd, recv_buf, sizeof(recv_buf) - 1, 0);

    if (n < 0) {
      perror("recv failed");
      break;
    } else if (n == 0) {
      printf("Server closed the connection.\n");
      break;
    }

    printf("%s", recv_buf);
  }

  close(sockfd);
  return 0;
}
