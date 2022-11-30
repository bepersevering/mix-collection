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


int my_strspn(const char *str, const char *accept) {
  const char *si;
  const char *ai;
  int count = 0;
  for (si = str; *si != '\0'; si++) {
    for (ai = accept; *ai != '\0'; ai++) {
      if (*si == *ai) {
        break;
      }
    }
    if (*ai == '\0') {
      return count;
    }
    ++count;
  } 
  return count;
}

char * my_strpbrk(const char * cs,const char * ct) {
  const char *csp, *ctp;
  for (csp = cs; *csp != '\0'; csp++) {
    for (ctp = ct; *ctp != '\0'; ctp++) {
      if (*csp == *ctp) {
        return (char *)csp;
      }
    }
  }
  return NULL;
}


char * my_strchr(char* s,char c) {
  while (*s != '\0' && *s != c) {
    ++s;
  }
  return *s == c ? s : NULL;
}

/** 
 * Parse S into tokens separated by characters in DELIM. 
 *     If S is NULL, the saved pointer in SAVE_PTR is used as 
 *     the next starting point.  For example: 
 *          char s[] = "-abc-=-def"; 
 *          char *sp; 
 *          x = strtok_r(s, "-", &sp);      // x = "abc", sp = "=-def" 
 *          x = strtok_r(NULL, "-=", &sp);  // x = "def", sp = NULL 
 *          x = strtok_r(NULL, "=", &sp);   // x = NULL 
 *                  // s = "abc\0-def\0"
 * （1）判断参数s是否为NULL，如果是NULL就以传递进来的save_ptr作为起始分解位置；若不是NULL，则以s开始切分。
 * 
 * （2）跳过待分解字符串开始的所有分界符。
 * 
 * （3）判断当前待分解的位置是否为'\0'，若是则返回NULL；不是则继续。
 * 
 * （4）保存当前的待分解串的指针token，调用strpbrk在token中找分界符：如果找不到，则将save_ptr赋值为待分解串尾部'\0'所在的位置，token没有发生变化；若找的到则将分界符所在位置赋值为'\0'，token相当于被截断了（提取出来），save_ptr指向分界符的下一位。
 * 
 * （5）函数的最后（无论找到还是没找到）都将返回。
 * ————————————————
 * 版权声明：本文为CSDN博主「jasmineal」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
 * 原文链接：https://blog.csdn.net/jasmineal/article/details/8981339
 * 
 * 附：调用strtok_r函数时，分割字符串后将结果赋值给具体的指针变量后，指针变量存放的是原目标字符串的地址，
 * 通过strtor_r处理后，是将分隔符的位置用'\0'代替了，使用时需注意到这点。
**/ 
char *my_strtok_r(char *str, const char *delim, char **saveptr) {
  // 实现：
  char *token;
  if (str == NULL) {
    str = *saveptr;
  }

  // str指向第一个不匹配delim的字符位置
  str += strspn(str, delim);
  if (*str == '\0'){
    return NULL;
  }
  token = str;
  str = my_strpbrk(token, delim);
  if (str == NULL) {
    *saveptr = my_strchr(token, '\0');
  } else {
    *str = '\0';
    *saveptr = str + 1;
  }

  return token;
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
  char str[] = "root:x::0:root:/root:/bin/bash:";
  char *token;
  char *p = str;
  char **saveptr = &(p);
  token = my_strtok_r(str, "%:%", saveptr);
  printf("%s\n", token);
  while ((token = my_strtok_r(NULL, "%:%", saveptr))!= NULL) {
    printf("%s\n", token);
  }
}

void test_my_strtok_r1() {
  char *str1 = "a/bbb///cc;xxx:yyy:";
  char *d1 = ":;";
  char *d2 =  "/";

  char str[] = "root:x::0:root:/root:/bin/bash:";
  char *token;

  char *p = str;
  char **saveptr = &(p);
  token = my_strtok_r(str, "%:%", saveptr);
  printf("%s\n", token);
  while ((token = my_strtok_r(str, "%:%", saveptr))!= NULL) {
    printf("%s\n", token);
  }
}

void test_my_strspn(void) {
  char *str = "aabbccddeeffgbbccaa";
  char *accept = "g";

  int index = my_strspn(str, accept);

  printf("index = %d\n", index);
}

int main(void) {
  // test_my_strspn();
  // test_my_strtok();
  test_my_strtok_r();

  return 0;
}
