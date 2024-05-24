#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main() {
  char cmd[50];

  strcpy(cmd, "ls -l");

  system(cmd);

  return 0;
}
