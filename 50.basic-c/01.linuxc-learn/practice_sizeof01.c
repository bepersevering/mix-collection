#include <stdio.h>

int main(void) {
  int a[12];

  printf("sizeof a %lu \n", sizeof a);
  printf("sizeof(a) %lu \n", sizeof(a));

  printf("sizeof(a[0] %lu \n", sizeof(a[0]));
  printf("sizeof(a) / sizeof(a[0]) %lu \n", sizeof(a)/sizeof(a[0]));
  return 0;
}
