#include <stdio.h>

int greatest_common_divisor(int a, int b) {
  if (a < b) {
    return greatest_common_divisor(b, a);
  }
  
  if (a % b == 0) {
    return b;
  }

  return greatest_common_divisor(b, a%b);
}

int main(void) {
  int a = 50, b = 125;
  
  int result = greatest_common_divisor(b, a);

  printf("%d and %d greatest common divisor is %d\n", a, b, result);

  return 0;
}
