#include <stdio.h>
#include <stdlib.h>
#define N 20

int a[N];

void gen_random(int upper_bound) {
  int i;
  for (i = 0; i < N; i++) {
    a[i] = rand() % upper_bound;
  }
}

void print_random() {
  int i;
  for (i = 0; i < N; i++) {
    printf("a[%d] = %d\t", i, a[i]);
  }
  printf("\n");
}
int main(void) {
  int i, j, histogram[10] = {};
  gen_random(10);
  for (i = 0; i < N; i++) {
    ++histogram[a[i]];
  }
  for (i = 0; i < 10; i++) {
    printf("histogram[%d] = %d\n", i, histogram[i]);
  }
  for (i = 0; i < 10; i++) {
    printf("%d\t", i);
  }
  printf("\n");
  for (i = 0; i < 10; i++) {
    for (j = 0; j < 10; j++) {
      if (histogram[j] > 0) {
	histogram[j] -= 1;
	printf("*\t");
      } else {
	printf(" \t");
      }
    }
    printf("\n");
  }
  return 0;
}
