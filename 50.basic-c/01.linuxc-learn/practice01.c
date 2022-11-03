#include <stdio.h>

void take_ones_tens(int x){
  int ones;
  int tens;
  ones = x / 1 % 10;
  tens = x / 10 % 10;
  printf("ones = %d, tens = %d\n", ones, tens);
  
}
int main(void) {
  int v = 10245;
  take_ones_tens(v);

  return 0;
}
