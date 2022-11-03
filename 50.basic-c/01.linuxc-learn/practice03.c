#include <stdio.h>

int count9(int n) {
  int i = 1;
  int result = 0;
  while (i <= n) {
    if (i % 10 == 9 || i / 10 == 9) {
      result++;
    }
    i++;
  }

  return result;
}

int main(void){
  int n = 100;

  int count = count9(n);

  printf("0 - 100 contains %d times of 9\n", count);

  return 0;
}
