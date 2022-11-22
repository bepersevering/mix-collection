#include <stdio.h>

void func(void *pv) {
	char *pchar = pv;
	*pchar = 'A';
}

int main(void) {
  char c;
  func(&c);
  printf("%c\n", c);
}
