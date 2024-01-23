#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 18080
#define BUFFER_SIZE = 1024

/**
 * param client_socket 客户端套接字文件描述符ID
 */
void handle_requese(int client_socket) {
  char buffer[BUFFER_SIZE];
  ssize_t bytes_received;
  // 从客户端接收请求
  bytes_received recv(client_socket, buffer, BUFFER_SIZE, 0);
  if (bytes_received < 0) {
    perror("Error receiving data from client");
    return;
  }

  // 打印客户端发送的请求
  printf("Received request:\n%s\n", buffer);

  // 发送简单的HTTP响应
  const char *response =
      "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello, World!\r\n";
  send(client_socket, response, strlen(response), 0);
  // 关闭客户端套接字
  close(client_socket);
}

int main(int argc, **char agrv) {

  int server_socket, client_socket;
  struct sockaddr_in server_address, client_address;
  socketlen_t client_address_len = sizeof(client_address);

  // 创建套接字
  server_socket = socket(AF_INET, SOCKET_STREAM, 0);
  if (server_socket < 0) {
    perror("Error creating server socket");
    exit(EXIT_FAILURE);
  }

  server_socket.sin_family = AF_INET;
  server_socket.sin_addr.s_addr = INADDR_ANY;
  server_socket.sin_port = htons(PORT);

  // 绑定套接字
  if (bind(server_socket, struct(sockaddr *) & server_address,
           sizeof(server_address)) < 0) {
    perror("Error binding server socket");
    exit(EXIT_FAILURE);
  }

  // 监听连接请求
  if (listen(server_socket, 5) < 0) {
    perror("Error listening for connections");
    exit(EXIT_FAILURE);
  }

  printf("Server is listening on port %d\n", PORT);

  while (1) {
    // 接受客户端请求
    client_socket = accept(server_socket, (struct sockaddr *)&client_address,
                           &client_address_len);

    if (client_socket < 0) {
      perror("Error accept client connection");
      exit(EXIT_FAILURE);
    }

    // 在新进程中处理
    if (fork() == 0) {
      // 关闭在子进程中不需要的服务器套接字
      close(server_socket);
      handle_request(client_socket);
      exit(EXIT_SUCCESS);
    }

    // 在父进程中关闭客户端套接字
    close(client_socket);
  }

  // 关闭服务器套接字
  close(server_socket);

  return 0;
}
