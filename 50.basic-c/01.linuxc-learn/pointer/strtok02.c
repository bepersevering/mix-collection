#include <stdio.h>
#include <string.h>

char *my_strtok(char *str, const char *delim);
char *my_strtok_r(char *str, const char *delim, char **saveptr);

int is_delim(char ch, const char *delim) {
  while (*delim != '\0') {
    if (ch == *delim) {
      return 1;
    }
    delim++;
  }
  return 0;
}

char *my_strtok(char *str, const char *delim) {
  static char *backup;
  if(!str) {
    str = backup;
  }
  if(!str) {
    return NULL;
  }
  
  while (1) {
    if (is_delim(*str, delim)) {
      str++;
      continue;
    }
    if (*str == '\0') {
      return NULL;
    }
    break;
  }

  char *ret = str;
  while (1) {
    if (*str == '\0') {
      backup = str;
      return ret;
    }
    if (is_delim(*str, delim)) {
      *str = '\0';
      backup = str+1;
      return ret;
    }
    str++;
  }
  
  

}

int main(void) {
  char str[] = "root:x::0:root:/root:/bin/bash:";
  char *token;

  token = strtok(str, "%:%");
  printf("%s\n", token);
  while ((token = strtok(NULL, "%:%"))!= NULL) {
    printf("%s\n", token);
  }
  return 0;
}