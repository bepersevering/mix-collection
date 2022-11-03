#include <stdio.h>

int is_leap_year(int year) {
  if (year % 400 == 0) {
    return 1;
  }
  if (year % 4 == 0 && year % 100 != 0) {
    return 1;
  }

  return 0;
}

int main() {
  int year = 2022;
  if (is_leap_year(year)) {
    printf("%d is leap year.\n", year);
  } else {
    printf("%d is not leap year.\n",year);
  }
  return 0;
}
