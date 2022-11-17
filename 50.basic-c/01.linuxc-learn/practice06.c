#include <stdio.h>

int main(int argc, char *argv[]) {
  struct {
    char a;
    short b;
    int c;
    char d;
  } s;

  struct {
    char a;
    short b;
    int c;
    char d;
  } __attribute__((packed)) m ;
  
  s.a = 1;
  s.b = 2;
  s.c = 3;
  s.d = 4;

  printf("%u\n", sizeof(s));

  m.a = 1;
  m.b = 2;
  m.c = 3;
  m.d = 4;

  printf("%u\n", sizeof(m));
  return 0;

}
