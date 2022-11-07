#include <stdio.h>

int main(void) {
  struct complex_struct {double x, y;};
  struct complex_struct z1 = {3.0, 4.0};
  struct complex_struct z2 = z1;

  printf("z1 = %f+%f\n", z1.x, z1.y);
  printf("z2 = %f+%f\n", z2.x, z2.y);
  return 0;
}
