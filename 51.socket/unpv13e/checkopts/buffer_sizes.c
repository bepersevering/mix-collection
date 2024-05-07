#include <asm-generic/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main(int argc, char **argv) {
  int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
  int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);

  if (tcp_socket == -1 || udp_socket == -1) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  int tcp_send_buffer, tcp_recv_buffer;
  int udp_send_buffer, udp_recv_buffer;

  socklen_t optlen = sizeof(int);

  if (getsockopt(tcp_socket, SOL_SOCKET, SO_SNDBUF, &tcp_send_buffer, &optlen) == -1 ||
      getsockopt(tcp_socket, SOL_SOCKET, SO_RCVBUF, &tcp_recv_buffer, &optlen) == -1 ||
      getsockopt(udp_socket, SOL_SOCKET, SO_RCVBUF, &udp_send_buffer, &optlen) == -1 ||
      getsockopt(udp_socket, SOL_SOCKET, SO_RCVBUF, &udp_recv_buffer, &optlen) == -1)  {

    perror("getsockopt failed");
    exit(EXIT_FAILURE);
  }

  printf("TCP send buffer size: %d\n", tcp_send_buffer);
  printf("TCP receive buffer size: %d\n", tcp_recv_buffer);

  printf("UDP send buffer size: %d\n", udp_send_buffer);
  printf("UDP receive buffer size: %d\n", udp_recv_buffer);

  close(tcp_socket);
  close(udp_socket);

  return 0;
}
