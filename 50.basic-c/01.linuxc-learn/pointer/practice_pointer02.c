#include <stdio.h>

int *swap(int *px, int *py) {
  int temp;
  temp = *px;
  *px = *py;
  *py = temp;
  return px;
}

int main(void) {
  int i = 20, j = 10;
  int *p = swap(&i, &j);
  printf("now i=%d, j=%d, *p = %d\n", i, j, *p);

  return 0;
}
