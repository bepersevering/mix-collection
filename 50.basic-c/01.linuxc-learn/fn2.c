#include <stdio.h>

void newLine(void) {
  printf("\n");
}

void threeLine(void) {
  newLine();
  newLine();
  newLine();
}

int main(void) {
  printf("Three lines:\n");
  threeLine();
  printf("Another three lines.\n");
  threeLine();
  return 0;
}
