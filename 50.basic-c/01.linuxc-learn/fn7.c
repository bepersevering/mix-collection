#include "stdio.h"
#include "string.h"

#define MAXN 1024
int main(int argc, char *argv[]) {

  char *str = "aa bb cc \n dd ee \n ff \n \0";
  char buf[MAXN];
  char p[MAXN];
  int pi;

  for (pi = 0; pi < strlen(str); pi++) {
    buf[pi] = str[pi];
  }
  buf[pi] = '\0';
  pi = 0;

  for (int i = 0; i < strlen(buf); i++) {
    if (buf[i] == '\n') {
      p[pi] = '\0';
      printf("%s\n", p);
      *p = 0;
      pi = 0;
    } else {
      p[pi++] = buf[i];
    }
  }

  return 0;
}
