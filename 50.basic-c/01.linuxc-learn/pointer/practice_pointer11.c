#include <stdio.h>

int main(void) {
  const char *s1 = "test";
  char *s2 = s1;

  s2 = "it's modified";

  printf("%s\n", s1);

  return 0;
}
