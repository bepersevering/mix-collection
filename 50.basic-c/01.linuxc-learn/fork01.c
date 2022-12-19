#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  pid_t pid;
  char *msg;
  int n;
  pid = fork();
  if (pid < 0) {
    perror("fork failed");
    exit(1);
  }

  if (pid == 0) {
    msg = "This is the child\n";
    n = 6;
  } else {
    msg = "This is the parent\n";
    n = 3;
  }

  for (; n > 0; n--) {
    printf(msg);
    sleep(1);
  }
  
  return 0;
}
