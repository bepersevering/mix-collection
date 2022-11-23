#include <stdio.h>

int main(void) {
  int data[10][10] = {};

  int i, j;
  for (i = 0; i < 10; i++) {
    for(j = 0; j < 10; j++) {
      data[i][j] = 10*i + j;
    }
  }

  for (i = 0; i < 10; i++) {
	for (j = 0; j < 10; j++) {
		printf("%d\t", data[i][j]);
	}
	printf("\n");
  }

  printf("------------------------\n");
  
  int *a[10] = {};
  for (i = 0; i < 10; i++) {
    a[i] = &data[i][0];
  }

  for(i = 0; i < 10; i++) {
    for (j = 0; j < 10; j++) {
      printf("%d\t", *(a[i] + j));
    }
    printf("\n");
  }

  printf("--------------------------\n");
  int (*b)[10] = &data[0];
  for (i = 0; i < 10; i++) {
    printf("%d\t", (*b)[i]);
  }

  printf("\n");

  
  return 0;
}
