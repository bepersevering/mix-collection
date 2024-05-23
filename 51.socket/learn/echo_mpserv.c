#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/socket.h>


#define BUF_SIZE 30
void error_handling(char *msg);
void read_childproc(int sig);

int main(int argc, char **argv) {

}
