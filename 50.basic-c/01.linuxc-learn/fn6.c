#include <stdio.h>

int main(void) {
  int i = 0;
  for (; i <= 1024; ++i) {
    if ((i & 0xff) == 0) {
      printf("%d\n", i);
    }
  }

  return 0;
}
