#include <stdio.h>
#include <unistd.h>

#define BUF_SIZE 30

int main(int argc, char **argv) {
  int p[2];
  char str1[] = "Who are you?";
  char str2[] = "Thank you for your message";

  char buf[BUF_SIZE];

  pid_t pid;

  pipe(p);

  pid = fork();

  if (pid == 0) {
    // child process
    write(p[1], str1, sizeof(str1));
    sleep(2);
    read(p[0], buf, BUF_SIZE);
    printf("Child proc output: %s \n", buf);
  } else {
    // parent process
    read(p[0], buf, BUF_SIZE);
    printf("Parent proc output: %s \n", buf);
    write(p[1], str2, sizeof(str2));
    sleep(3);
  }

  return 0;
}
