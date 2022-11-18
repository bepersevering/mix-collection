#include <stdio.h>

typedef union{
  unsigned int x;
  unsigned char byte[4];
} demo_type;

int main(void) {
  demo_type u = {0x11223344};

  printf("u.x = 0x%8x\n", u.x);
  printf("hex dump = %x %x %x %x \n", u.byte[0], u.byte[1], u.byte[2], u.byte[3]);
  return 0;
}
