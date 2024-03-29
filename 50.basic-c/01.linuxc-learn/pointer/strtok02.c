#include <stdio.h>
#include <string.h>

char *my_strtok(char *str, const char *delim);
char *my_strtok_r(char *str, const char *delim, char **saveptr);


int match_delim(char ch, const char *delim) {
  while (*delim != '\0') {
    if (ch == *delim) {
      return 1;
    }
    delim++;
  }
  
  return 0;
}

// my strtok implement
char *my_strtok(char *str, const char *delim) {
  
  // backup str for the next strtok
  static char *backup;
  
  // check str is NULL
  if (str == NULL) {
    str = backup;
  } else {
    backup = str;
  }
  
  if (!(*str)) {
    return NULL;
  }

  while (1) {
    if (match_delim(*str, delim)) {
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
    
    if (match_delim(*str, delim)) {
      backup = str + 1;
      *str = '\0';
      return ret;
    }

    str++;
  }

  return NULL;
}

char *my_strtok_r(char *str, const char *delim, char **saveptr) {
  // 实现：
  // 1.如果str为空，或者str = '\0' 返回空
  // 1.如果**saveptr指向的是str的最后一个，则返回空
  // 循环遍历第一个
}



void test_my_strtok() {
  char str[] = "root:x::0:root:/root:/bin/bash:";
  char *token;

  token = my_strtok(str, "%:%");
  printf("%s\n", token);
  while ((token = my_strtok(NULL, "%:%"))!= NULL) {
    printf("%s\n", token);
  }
}

void test_my_strtok_r() {
  char *str1 = "a/bbb///cc;xxx:yyy:";
  char *d1 = ":;";
  char *d2 =  "/";

  char str[] = "root:x::0:root:/root:/bin/bash:";
  char *token;

  char **p;
  token = my_strtok_r(str, "%:%", p);
  printf("%s\n", token);
  while ((token = my_strtok_r(str, "%:%", p))!= NULL) {
    printf("%s\n", token);
  }
}


int main(void) {
  
  // test_my_strtok();
  test_my_strtok_r();

  return 0;
}
