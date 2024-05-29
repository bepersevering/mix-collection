#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv){
  int status;

  pid_t pid = fork();

  if (pid == 0) {
    // child process
    sleep(15);
    return 24;
  } else {
    while (!waitpid(pid, &status, WNOHANG)) {
      sleep(3);
      puts("sleep 3 sec.");
    }
    if (WIFEXITED(status)) {
      printf("child send %d \n", WEXITSTATUS(status));
    }
  }

  return 0;
}
