#include <stdio.h>

int main(void) {
  int data[10][10] = {};

  int i, j;
  for (i = 0; i < 10; i++) {
    for(j = 0; j < 10; j++) {
      data[i][j] = 10*i + j;
    }
  }

  int *a[10] = data[0][10];

  // int *a[10] = {};

  // for (i = 0; i< 10; i++) {
	// *a[i] = data[i][10];
  // }

  int **pa = &a[0];

  return 0;
}
