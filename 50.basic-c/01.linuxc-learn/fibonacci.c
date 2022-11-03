#include <stdio.h>

int fibonacci(int n) {
  if (n == 0 || n == 1) {
    return 1;
  }

  return fibonacci(n - 1) + fibonacci(n - 2);

}

int main(void) {
  int n = 10;
  int result = fibonacci(n);

  printf("fibonacci(%d) = %d\n", n, result);
  return 0;
}
