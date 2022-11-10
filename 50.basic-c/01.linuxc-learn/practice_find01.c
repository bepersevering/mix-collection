#include <stdio.h>

char a[] = "hello World";

int indexOf(char letter) {
  int i = 0;
  while(a[i] != '\0') {
    if (a[i] == letter) {
      return i;
    }
    i++;
  }

  return -1;
}

int main(void) {
  printf("%d %d\n",indexOf('o'), indexOf('z'));
  return 0;
}
