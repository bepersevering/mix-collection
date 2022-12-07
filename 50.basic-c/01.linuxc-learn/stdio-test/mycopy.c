#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void copy(char *file1, char *file2) {
  FILE *fp1 = fopen(file1, "r");
  if (fp1 == NULL) {
    perror(strcat("Open file ", file1));
    exit(1);
  }
  
  FILE *fp2 = fopen(file2, "w+");
  if (fp2 == NULL) {
    perror(strcat("Open file ", file2));
    exit(1);
  }

  int ch;
  while ((ch = fgetc(fp1)) != EOF) {
    fputc(ch, fp2);
  }

  fclose(fp1);
  fclose(fp2);
}

int main(void) {
  copy("testfile1", "testfile2");
  return 0;
}