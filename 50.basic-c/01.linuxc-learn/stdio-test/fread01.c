#include <stdio.h>
#include <stdlib.h>

struct record {
  char name[10];
  int age;
};

int main(void) {
  struct record array[2];
  FILE *fp = fopen("recfile", "r");
  if (fp == NULL) {
    perror("Open file recfile");
    exit(1);
  }

  fread(array, sizeof(struct record), 2, fp);
  printf("Name1: %s\t Age1: %d\n", array[0].name, array[0].age);
  printf("Name2: %s\t Age2: %d\n", array[1].name, array[1].age);
  
  return 0;
}
