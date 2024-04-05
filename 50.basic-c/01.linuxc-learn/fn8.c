#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int p[2];
  pipe(p);
  char *s = "abc \\0 e f g h";
  char buf[128];

  write(p[1], s, strlen(s));
  close(p[1]);

  while (read(p[0], buf, 128) > 0) {
    printf("buf -> %s\n", buf);
  }
  close(p[0]);

  return 0;
}
