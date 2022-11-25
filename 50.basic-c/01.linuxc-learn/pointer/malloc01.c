#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int number;
  char *msg;
} unit_t;

int main(void) {
  unit_t *p = malloc(sizeof(unit_t));

  if (p == NULL) {
    printf("out of memory\n");
    exit(1);
  }
  
  p->number = 11;
  p->msg = malloc(20);

  if (p->msg == NULL) {
    printf("out of memory\n");
    exit(1);
  }
  
  strcpy(p->msg, "Hello World!");

  printf("number: %d\nmsg: %s\n", p->number, p->msg);


  // free
  free(p->msg);
  free(p);
  p = NULL;
  
  return 0;
}
