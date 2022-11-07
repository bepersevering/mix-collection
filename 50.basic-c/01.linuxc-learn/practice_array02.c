#include <stdio.h>

int main(void) {
  int array1[5] = {1, 3, 5, 7, 9};
  int array2[5] = {2, 4, 6, 8, 10};
  int i;
  for(i = 0; i < 5; i++) {
    printf("array1[%d] = %d\n", i, array1[i]);
    printf("array2[%d] = %d\n", i, array2[i]);
  }
  for(i = 0; i < 5; i++) {
    array2[i] = array1[i];
  }

  for (i = 0; i < 5; i++) {
    printf("array1[%d] = %d\n", i, array1[i]);
    printf("array2[%d] = %d\n", i, array2[i]);
  }
  
  return 0;
}
