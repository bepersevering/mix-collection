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
  gen_random(10);
  print_random();
  return 0;
}
