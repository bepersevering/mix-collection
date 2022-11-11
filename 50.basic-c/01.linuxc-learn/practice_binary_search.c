#include <stdio.h>

#define LEN 8

int a[LEN] = {1, 2, 3, 5, 7, 8, 10, 23};

int binarySearch(int element) {
  int mid, left = 0, right = LEN - 1;

  while (left <= right) {
    mid = left + (right - left)/2;
    if (a[mid] < element) {
      left = mid+1;
    } else if (a[mid] > element) {
      right = mid - 1;
    } else {
      return mid;
    }
  }
  return -1;
}

int main(void) {
  printf("%d\n", binarySearch(23));
  return 0;
}
