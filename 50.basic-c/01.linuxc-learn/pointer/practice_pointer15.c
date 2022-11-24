#include <stdio.h>

void say_hello(const char *str) {
  printf("hello %s\n", str);

}

int main(void) {
  void (*f)(const char *str) = say_hello;
  void (*ff)(const char *str) = &say_hello;

  f("小明");
  (*f)("小明");
 

  ff("小张");
  (*ff)("小张");

  
  return 0;
}
