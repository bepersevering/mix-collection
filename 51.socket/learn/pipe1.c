#include <stdio.h>
#include <unistd.h>

#define BUF_SIZE 30

int main(int argc, char **argv) {
  int p[2];

  char str[] = "Who are you?";
  char buf[BUF_SIZE];

  pid_t pid;

  pipe(p);

  pid = fork();
  if (pid == 0) {
    // child process
    write(p[1], str, sizeof(str));
  } else {
    // parent process
    read(p[0], buf, BUF_SIZE);
    puts(buf);
  }

  return 0;
}
