#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

int main(int argc, char **argv) {
  char *ptr, **pptr;
  char str[INET_ADDRSTRLEN];

  struct hostent *hptr;

  while(--argc > 0) {
    ptr = *++argv;
    if ((hptr = gethostbyname(ptr)) == NULL) {
      printf("gethostbyname error for host: %s: %s", ptr,
             hstrerror(h_errno));
      continue;
    }
    printf("offical hostname: %s\n", hptr->h_name);

    for (pptr = hptr->h_aliases; *pptr != NULL; pptr++) {
      printf("\talias: %s\n", *pptr);
    }

    switch (hptr->h_addrtype) {
      case AF_INET:
        pptr = hptr->h_addr_list;
        for (; *pptr != NULL; pptr++) {
          printf("\taddress: %s\n", 
                 inet_ntop(hptr->h_addrtype, 
                           *pptr, str, sizeof(str)));
          break;
        }
      default:
        perror("unknown address type");
        break;
    }
  }

  exit(0);
}
