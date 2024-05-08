#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>

#define SERV_PORT 9909
#define MAXLINE 4096

void dg_cli(FILE *, int, struct sockaddr *, socklen_t);

int main(int argc, char **argv) {
  int sockfd;

  struct sockaddr_in servaddr;

  if (argc != 2) {
    perror("usage: udpcli01 <IPaddress>");
    exit(EXIT_FAILURE);
  }

  bzero(&servaddr, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(SERV_PORT);

  if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
    perror("inet_pton error");
    exit(EXIT_FAILURE);
  }

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd == -1) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  dg_cli(stdin, sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

  exit(0);
}

char *sock_ntop(const struct sockaddr *sa, socklen_t salen) {
  char portstr[8];
  // unix domain is largest
  static char str[128];

  switch (sa->sa_family) {
  case AF_INET: {
    struct sockaddr_in *sin = (struct sockaddr_in *)sa;

    if (inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)) == NULL) {
      return NULL;
    }
    if (ntohs(sin->sin_port) != 0) {
      snprintf(portstr, sizeof(portstr), ":%d", ntohs(sin->sin_port));
      strcat(str, portstr);
    }
    return (str);
  }
  default:
    snprintf(str, sizeof(str), "sock_ntop: unknown AF_xxx: %d, len %d",
             sa->sa_family, salen);
    return (str);
  }
  return (NULL);
}

void dg_cli(FILE *fp, int sockfd, struct sockaddr *servaddr,
            socklen_t servlen) {
  int n;
  char sendline[MAXLINE], recvline[MAXLINE + 1];
  socklen_t len;
  struct sockaddr *preply_addr;
  struct sockaddr_in reply_addr_in;
  bzero(&reply_addr_in, sizeof(reply_addr_in));

  preply_addr = malloc(servlen);

  while (fgets(sendline, MAXLINE, fp) != NULL) {
    sendto(sockfd, sendline, strlen(sendline), 0, servaddr, servlen);

    n = recvfrom(sockfd, recvline, MAXLINE, 0, preply_addr, &len);
    if (len != servlen || memcmp(preply_addr, servaddr, len) != 0) {
      printf("reply form %s (ignored)\n",
             sock_ntop(preply_addr, len));
      continue;
    }
    if (n <= 0) {
      perror("recvfrom failed");
      continue;
    }

    // null terminate
    recvline[n] = '\0';

    fputs(recvline, stdout);
  }
}
