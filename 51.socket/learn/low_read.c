#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 1024

void error_handling(char *msg);


int main(void) {
  int fd;

  char buf[BUF_SIZE];

  fd = open("data.txt", O_RDONLY);

  if (fd == -1) {
    error_handling("open() error!");
  }

  printf("file data: %s\n", buf);

  close(fd);
  return 0;
}


void error_handling(char *msg) {
  fputs(msg, stderr);
  fputc('\n', stderr);
  exit(1);
}


