#include <stdio.h>
#include <errno.h>


int main(void) {
  int a = 10, b;
  __asm__("movl %1, %%eax\n\t"
	  "movl %%eax, %0\n\t"
	  : "=r"(b)
	  : "r"(a)
	  : "%eax"
	  );

  printf("Result: a = %d, b = %d\n", a, b);
  return 0;
}
