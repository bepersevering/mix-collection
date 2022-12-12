#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
  
  char str1[] = "a/bbb///cc;xxx:yyy:";
  char *str2 = str1;

  printf("%s\n", str2);
  const char *delim = ":;";
  char *saveptr = str2;
  char *token = strtok_r(str2, delim, &saveptr);

   printf("%s\n", token);
   while ((token = strtok_r(saveptr, delim, &saveptr)) != NULL) {
     printf("%s\n", token);
   }
  
  return 0;
}
