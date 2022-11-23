#include <stdio.h>

int main(void) {
  int i, j;
  int a[10] = {10,9,8,7,6,5,4,3,2,1};
  int (*p)[10] = &a;

  for (i = 0; i < 10; i++) {
    printf("%d\t", (*p)[i]);
  }

  printf("\n---------------------------\n");
  
  int data[10][10] = {};

  for (i = 0; i < 10; i++) {
    for (j = 0; j < 10; j++) {
      data[i][j] = i*10 + j;
    }
  }

  for (i = 0; i < 10; i++) {
    for (j = 0; j < 10; j++) {
      printf("%d\t", data[i][j]);
    }

    printf("\n");
  }

  printf("----------------------------\n");


  int (*pa)[10] = &data[0];

  for(i = 0; i < 10; i++) {
    for (j = 0; j < 10; j++) {
      printf("%d\t", pa[i][j]);
    }
    printf("\n");
  }

  return 0;

}
