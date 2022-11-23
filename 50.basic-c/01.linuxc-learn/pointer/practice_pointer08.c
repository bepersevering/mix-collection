#include <stdio.h>

int main(void) {


  char x = 'A';
  char *xp = &x;
  char **xpp = &xp;

  printf("x = %c\n", x);
  printf("*xp = %c\n", *xp);
  printf("**xpp = %c\n", **xpp);
  
  
  char str[] = "hello world";
  
  char *p = str;
  const char *cp = str;
  
  char const **p1 = &p;
  char const **p2 = &cp;
  
  printf("str = %s\n", str);

  printf("*p = %c\n", *p);
  printf("*cp = %c\n", *cp);
  
  printf("**p1 = %c\n", **p1);
  printf("**p2 = %c\n", **p2);
  
  return 0;

}
