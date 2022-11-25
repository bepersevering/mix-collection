#include <stdio.h>
#include <stdlib.h>

int main(void) {
  long long size = 0;
  long long t = 40960;
  int *p;
  while (p != NULL) {
    p = malloc(t);

    size += t;
    printf("size = 0x%lX\n", size); 
  }


  return 0;

}
