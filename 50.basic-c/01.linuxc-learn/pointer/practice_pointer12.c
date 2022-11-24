#include <stdio.h>

int main(void) {
  int a = 3;
  char s1[] = "test";

  int b = 4;
  char s2[] = "test2";

  printf("the address of a is %u\n", &a);
  printf("s1 is %u\n", s1);
  printf("the address of s1 is %u\n", &s1);
  printf("the address of b is %u\n", &b);
  printf("s2 is %u\n", s2);
  printf("the address of s2 is %u\n", &s2);

  return 0;
}
