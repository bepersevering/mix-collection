#include <stdio.h>
#include <string.h>

int main() {
  char foo[10] = "foo";
  char bar[10] = "bar";

  strncat(foo, bar, 2);
  printf("foo = %s, bar = %s\n", foo, bar);

  return 0;
}
