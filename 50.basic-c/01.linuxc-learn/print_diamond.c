#include <stdio.h>

void print_diamond(int n) {
  // if is odd, print error
  if (n % 2 == 0) {
    printf("parameter %d error, paramenter should be even\n", n);
  }
  int top = (n + 1)/2;
  int i, j, k;
  int start, end;
  // top
  for (i = 1; i <= top; i++) {    
    start = top + 1 - i;
    end = (2*i - 1) + start - 1;

    for (j = 1; j <= n; j++) {
      if (j >= start && j <= end) {
	printf("*");
      } else {
	printf(" ");
      }
    }
    printf("\n");
  }
  
  // below
  for (i = top + 1; i <= n; i++) {
    k = n + 1 - i;
    start = top + 1 - k;
    end = (2*k - 1) + start - 1;
    for (j = 1; j <= n; j++) {
      if (j >= start && j <= end) {
	printf("*");
      } else {
	printf(" ");
      }
    }
    printf("\n");
  }
  
}

int main(void) {
  int n = 5;
  print_diamond(n);
  return 0;
}
