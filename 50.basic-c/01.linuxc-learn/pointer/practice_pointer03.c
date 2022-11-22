#include <stdio.h>

int main(void) {
  int i = 3;
  const int *a = &i;

  printf("*a = %d, a = 0x%x, a++=0x%x\n", *a, a, (a++));

  return 0;
}
