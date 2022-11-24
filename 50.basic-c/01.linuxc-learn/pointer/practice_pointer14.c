#include <stdio.h>

int main(void) {
  char *buf = "hello";

  buf[0] = 'a';

  printf("thre buf is %s\n", buf);

  return 0;
}
