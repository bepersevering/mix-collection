#include <stdio.h>
#include "para_callback.h"

void say_hello(void *str) {
  printf("Hello %s\n", (const char *)str);
}

void count_numbers(void *num) {
  int i;
  for (i = 1; i <= (int)num; i++) {
    printf("%d ", i);
  }

  printf("\n");
}

int main(void) {
  repeat_three_times(say_hello, "Guys");
  repeat_three_times(count_numbers, (void *)4);

  return 0;
}
