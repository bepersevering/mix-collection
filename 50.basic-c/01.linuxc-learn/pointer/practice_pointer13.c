#include <stdio.h>

int main(void) {
  int buf[4] = {0, 0, 0, 0};

  const int a = 10;
  buf[4] = 97;

  printf("a = %d\n", a);

  return 0;
}
