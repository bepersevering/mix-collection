#include <stdio.h>

int a,b = 1;

int main(void) {
  push('a');
  push('b');
  push('c');

  while(!isEmpty()) {
    putchar(pop());
  }

  putchar('\n');

  return 0;
}

