#include <stdio.h>

void print_diamond(int n) {
  if (n % 2 == 0){
    printf("n should be even\n");
    return;
  }
  
  int i, j, k;
  int mid = (n + 1) / 2;
  for (i = 1; i <= mid; i++) {
    for (j = 1; j <= (mid - i); j++) {
      printf(" ");
    }
    for (j = 1; j <= (i * 2 - 1); j++) {
      printf("*");
    }
    printf("\n");
  }

  for (i = mid + 1; i <= n; i++) {
    for (j = 1; j <= (i - mid); j++) {
      printf(" ");
    }
    for (j = 1; j <= (2*n - 2*i + 1); j++) {
      printf("*");
    }
    printf("\n");
  }

}
int main(void) {
  int n = 7;
  print_diamond(n);
  return 7;
}
