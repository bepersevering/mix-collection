#ifndef PARA_ALLOCATOR_H
#define PARA_ALLOCATOR_H

typedef struct {
  int number;
  char *msg;
} unit_t;

extern void alloc_unit(unit **);
extern void free_unit(unit *);

#endif
