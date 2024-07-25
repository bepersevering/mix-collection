#include <stdio.h>

int main() {
  const char *str = "123 hello";
  int num;
  char word[10];

  sscanf(str, "%d%s", &num, word);
  printf("Number: %d\n", num);
  printf("Word: %s\n", word);
  
  return 0;
}
