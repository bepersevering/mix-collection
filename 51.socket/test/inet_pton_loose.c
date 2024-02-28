#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>


int inet_pton_loose(int af, const char *src, void *dst) {
  // 如果地址族为AF_INET且inet_pton 返回0，那就调用inet_aton看是否成功
  if (af == AF_INET) {
    if (inet_pton(AF_INET, src, dst) == 1) {
      return 1;
    } else {
      // If inet_pton fails, try inet_aton
      struct in_addr addr;
      if (inet_aton(src, &addr) != 0) {
        // If inet_aton succeeds, return IPv4-mapped IPv6 address
        struct in6_addr *ipv6_addr = (struct in6_addr *)dst;
        memset(ipv6_addr, 0, sizeof(*ipv6_addr));
        ipv6_addr->s6_addr[10] = 0xFF;
        ipv6_addr->s6_addr[11] = 0xFF;
        memcpy(ipv6_addr->s6_addr + 12, &addr.s_addr, sizeof(addr.s_addr));
        return 1;
      }
    }
  }

  // 如果地址族为AF-INET6且inet_pton返回0。那就调用inet_aton看是否成功
  return inet_pton(AF_INET6, src, dst);
}

int main(int argc, char **argv) {
  char ip_address[INET6_ADDRSTRLEN];

  const char *ip_input = "0xe";
  struct in6_addr ipv6_addr;
  if (inet_pton_loose(AF_INET6, ip_input, &ipv6_addr) == 1) {
    printf("IPV6 address: %s\n", inet_ntop(AF_INET6, &ipv6_addr, ip_address, INET6_ADDRSTRLEN));
  } else {
    printf("Conversion failed.\n");
  }

  return 0;
}