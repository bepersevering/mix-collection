#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include <netdb.h>

int main(int argc, const char * argv[]) {
    printf("hello client\n");

    int client_sockfd;
    int len;
    struct sockaddr_in remote_addr;
    char buf[BUFSIZ];
    memset(&remote_addr, 0, sizeof(remote_addr));
    remote_addr.sin_family = AF_INET;
    remote_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    remote_addr.sin_port = htons(8000);

    if ((client_sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return 1;
    }

    if (connect(client_sockfd, (struct sockaddr *)&remote_addr, 
        sizeof(struct sockaddr)) < 0) {
        perror("connect");
        return 1;
    }

    printf("connect to server\n");

    len = recv(client_sockfd, buf, BUFSIZ, 0);
    buf[len] = '\0';
    printf("%s", buf);

    while(1) {
        printf("Enter string to send");
        scanf("%s", buf);
        if (!strcmp(buf, "quit")) {
            break;
        }

        len = send(client_sockfd, buf, strlen(buf), 0);
        len = recv(client_sockfd, buf, BUFSIZ, 0);
        buf[len] = '\0';
        printf("received: %s\n", buf);
    }
    
    close(client_sockfd);

    return 0;
}
