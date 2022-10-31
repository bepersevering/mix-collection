#include <stdio.h>

void newLine(void) {
  printf("\n");
}

int main(void) {
  printf("First Line.\n");
  newLine();
  printf("Second Line.\n");

  return 0;
}
