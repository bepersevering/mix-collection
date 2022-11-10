#include <stdio.h>
#include <stdlib.h>

void genRandom(int array[], int size) {
  int i;
  for (i = 0; i < size; i++) {
    array[i] = rand()%100;
  }
}

void printArray(int array[], int size) {
  int i;
  for (i = 0; i < size; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");
}

// function to find the min element
int findMin(int array[], int size) {
  int i, min = array[0];
  for (i = 0; i < size; i++) {
    min = min > array[i] ? array[i] : min;
  }

  return min;
}

int main(void) {
  
  int n = 20, min;
  int array[20] = {};

  genRandom(array, n);

  printArray(array, n);

  min = findMin(array, n);
  printf("the min element in array is %d\n", min);

  return 0;
}
