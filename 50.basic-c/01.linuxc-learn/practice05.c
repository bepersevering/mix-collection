#include <stdio.h>

const int A = 10;
int a = 20;
static int b = 30;
int c;

int main(void) {
  static int a = 40;
  char b[] = "Hello World";
  register int c = 50;
  printf("Hello World %d\n", c);

  return 0;
}
