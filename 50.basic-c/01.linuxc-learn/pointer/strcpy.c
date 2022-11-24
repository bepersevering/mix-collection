#include <stdio.h>
char *strcpy(char *dest, const char *src) {

  //  int i;
  // for (i = 0; src[i] != '\0'; i++) {
  //   dest[i] = src[i];
  // }

  // return dest;

  while(*src != '\0')
    *(dest++) = *(src++);

  return dest;
}

int main(void) {
  char *hello = "hello world";

  char t[20] = {};

  strcpy(t, hello);

  printf("%s\n", t);
  
  return 0;
}
