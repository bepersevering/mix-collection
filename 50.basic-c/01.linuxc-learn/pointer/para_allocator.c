#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "para_allocator.h"

void alloc_unit(unit_t **pp) {
	unit_t *p = malloc(sizeof(unit_t));
	if (p == NULL) {
		printf("out of memory\n");
	}
	p->number = 3;
	p->msg = malloc(20);

	strcpy(p->msg, "Hello world");

	*pp = p;
}

void free_unit(unit_t *p) {
	free(p->msg);
	free(p);
}
