#include <stdio.h>
#include <unistd.h>

#define BUF_SIZE 30

int main(int argc, char **argv) {
  int p1[2], p2[2];
  char str1[] = "Who are you?";
  char str2[] = "Thand you for your message";
  char buf[BUF_SIZE];

  pid_t pid;
  pipe(p1);
  pipe(p2);

  pid = fork();

  if (pid == 0) {
    // 
    write(p1[1], str1, sizeof(str1));
    read(p2[0], buf, BUF_SIZE);
    printf("Child proc output: %s\n", buf);
  } else {
    read(p1[0], buf, BUF_SIZE);
    printf("Parent proc output: %s \n", buf);
    write(p2[1], str2, sizeof(str2));
    sleep(3);
  }
  return 0;
}

