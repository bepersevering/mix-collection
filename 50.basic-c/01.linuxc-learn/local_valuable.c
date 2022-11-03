#include <stdio.h>

void foo(void) {
  int i;
  int j;
  printf("i = %d,j = %d\n", i, j);
  j = 666;
  i = 777;
}
int main(void) {
  foo();
  foo();
  return 0;
}
