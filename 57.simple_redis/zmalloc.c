#include "zmalloc.h"
#include "config.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static size_t used_memory = 0;

void *zmalloc(size_t size) {
  void *ptr = malloc(size + sizeof(size_t));

  if (!ptr) {
    return NULL;
  }
#ifdef HAVE_MALLOC_SIZE
  used_memory += redis_malloc_size(ptr);
  return ptr;
#else
  *((size_t *)ptr) = size;
  used_memory += size + sizeof(size_t);
  return (char *)ptr + sizeof(size_t);
#endif
}

void *zrealloc(void *ptr, size_t size) {
#ifndef HAVE_MALLOC_SIZE
  void *realptr;
#endif
  size_t oldsize;
  void *newptr;
  if (ptr == NULL)
    return zmalloc(size);
#ifdef HAVE_MALLOC_SIZE
  oldsize = redis_malloc_size(ptr);
  newptr = realloc(ptr, size);
  if (!newptr)
    return NULL;
  used_memory -= oldsize;
  used_memory += redis_malloc_size(newptr);
  return newptr;
#else
  realptr = (char *)ptr - sizeof(size_t);
  oldsize = *((size_t *)realptr);
  newptr = realloc(realptr, size + sizeof(size_t));

  if (!newptr)
    return NULL;

  *((size_t *)newptr) = size;
  used_memory -= oldsize;
  used_memory += size;
  return (char *)newptr + sizeof(size_t);

#endif
}

void zfree(void *ptr) {
#ifndef HAVE_MALLOC_SIZE
  void *realptr;
  size_t oldsize;
#endif
  if (ptr == NULL)
    return;
#ifdef HAVE_MALLOC_SIZE
  used_memory -= redis_malloc_size(ptr);
  free(ptr);
#else
  realptr = (char *)ptr - sizeof(size_t);
  oldsize = *((size_t *)ptr);
  used_memory -= oldsize + sizeof(size_t);
  free(realptr);
#endif
}


char *zstrdup(const char* s) {
  size_t l = strlen(s) + 1;
  char *p = malloc(l);

  memcpy(p, s, l);
  return p;
}

size_t zmalloc_used_memory(void) {
  return used_memory;
}
