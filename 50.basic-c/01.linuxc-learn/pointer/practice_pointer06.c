#include <stdio.h>

int main(void) {
  const int i = 10;
  int *p = &i;
  const int *p1 = &i;
  int const *p2 = &i;

  int const *const p3 = &i;
  const int *const p4 = &i;

  *(p1++);

  printf("i = %d, *p = %d, *p1 = %d, *p2 = %d\n", i, *p, *p1, *p2);

  return 0;
}
