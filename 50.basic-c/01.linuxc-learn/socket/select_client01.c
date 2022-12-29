#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT  9999  //服务器端口
#define SERVER_IP   "127.0.0.1" //服务端IP
#define MAXLEN  4096 //缓冲区最大大小

int main(){

   int socketfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    servaddr.sin_port = htons(SERVER_PORT);

    int ret = connect(socketfd, (struct sockaddr*)&servaddr, sizeof(struct sockaddr_in));
    
    if(ret != 0){
        printf("connect server failed:error number:%d\n", errno);
        exit(-1);
    }
    
    while(1){
        
        const char *message = "this is from client message";
        ret = send(socketfd, message, strlen(message), 0);
        
        if(ret > 0){
            char recvbuf[MAXLEN] = {0}; 
            ret = recv(socketfd, recvbuf, MAXLEN, 0);
            if(ret > 0){
                printf("recv message from server:%s\n", recvbuf);
            }else if(ret == 0){
                printf("server has closed!\n");
                close(socketfd);
            } 
            else{
                printf("recv error :%d\n", errno);
                close(socketfd);
            }
        }
        sleep(1);
    }

    return 0;
}
