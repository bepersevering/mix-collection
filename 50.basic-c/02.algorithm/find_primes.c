#include "stdio.h"

int is_prime(int n) {
  if (n <= 1) {
    return 0;
  }
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      return 0;
    }
  }

  return 1;
}

void find_prime(int start, int end) {
  for (int i = start; i <= end; i++) {
    if (is_prime(i)) {
      printf("%d is prime\n", i);
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: start end\n");
    return 0;
  }
  int start = atoi(argv[1]);
  int end = atoi(argv[2]);
  find_prime(start, end);
  return 0;
}
