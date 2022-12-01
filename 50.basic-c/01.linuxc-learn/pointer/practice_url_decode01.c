#include <stdio.h>
#include <string.h>

void test(char *url) {
  char *backup = url;

  char *delim1 = "?";
  char *delim2 = "&";
  char *delim3 = "=";
  
  char *saveptr, *saveptr1;
  char *token = strtok_r(backup, delim1, &saveptr);
  char *token1;
  char *token2;
  printf("the url path = [%s]", token);

  while ((token1 = strtok_r(backup, delim2, saveptr)) != NULL) {
    saveptr1 = &(token1);
    token2 = strtok_r(token1, delim3, saveptr1);
    printf("key = [%s], ", token2);
    token2 = strtok_r(token1, delim3, &saveptr1);
    printf("value = [%s]\n", token2);
  }
  
}

int main(void) {
  char * url1 = "http://www.google.cn/search?complete=1&hl=zh-CN&ie=GB2312&q=linux&meta=";
  char * url2 = "http://www.baidu.com/s?wd=linux&cl=3";
  
  test(url1);
  test(url2);

  return 0;
} 
