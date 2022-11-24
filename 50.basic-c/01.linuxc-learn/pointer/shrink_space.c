#include <stdio.h>
#include <string.h>

char *shrink_space1(char *dest, const char *src, size_t n) {

  int i;
  int j;
  for (i = 0, j = 0; i < n; i++) {
    if (*(src+i) == ' ' || *(src+i) == '\t' || *(src+i) == '\r' || *(src+i) == '\n') {
      if ((j-1)>=0 && *(dest+j-1) == ' ') {
	continue;
      } else {
	*(dest+j) = ' ';
	j++;
      }
    } else{
      *(dest+j) = *(src+i);
      j++;
    }

  }

  *(dest+n) = '\0';
  return dest;
}

int main(void) {
  char *src = "   This   Content hoho is ok \n"
"           ok? \r"
"   \n\r\t + \n\n\n\n\r\r\r \r \r\r \n\n"
    "\r\r\r     file system"
"       uttered words ok ok ?"
 "     end."
"    ";


  size_t n = strlen(src);
  printf("len of src is %d\n", n);
  printf("%s\n", src);
  printf("--------------------------------\n");
  char dest[200] = {};

  shrink_space1(dest, src, n);
 
  printf("%s\n", dest);
  return 0;
}
