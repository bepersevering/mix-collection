#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
  
  char *str = "a/bbb///cc;xxx:yyy:";
  char str1[] = "a/bbb///cc;xxx:yyy:";
  const char *delim = ":;";
  char *saveptr;
  char *token = strtok_r(str1, delim, &saveptr);

  printf("%s\n", token);
  while ((token = strtok_r(str, delim, &saveptr)) != NULL) {
    printf("%s\n", token);
  }

  return 0;
}
