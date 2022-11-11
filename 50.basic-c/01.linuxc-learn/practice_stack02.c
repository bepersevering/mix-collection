#include <stdio.h>

#define LEN 3

char buf[LEN] = {'a', 'b', 'c'};

void print_backword(int pos) {
  if (pos == LEN) {
    return;
  }

  print_backword(pos+1);
  putchar(buf[pos]);
}

int main(void) {
  print_backword(0);

  putchar('\n');

  return 0;
}
