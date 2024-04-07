#include <stdio.h>

#define R 0
#define W 1

int main(int argc, char *argv[]) {
  int p[2];
  pipe(p);
  char *s1 = "wc";
  char *s2 = 0;
  if (fork() == 0) {
    // child process
    close(R);

  }
}

