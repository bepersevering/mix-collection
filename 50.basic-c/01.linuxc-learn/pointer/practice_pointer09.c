#include <stdio.h>

int main(void) {
  char arr[] = "tear up";
  char *ptr = arr;
  char * const *p = &ptr;

  **p = 'A';

  // *p = 0;

  p = 0;

  return 0;
}
