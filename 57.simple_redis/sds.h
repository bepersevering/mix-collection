#ifndef __SDS_H
#define __SDS_H

#include <cstddef>
#include <sys/types.h>

typedef char *sds;

struct sdshdr {
  long len;
  long free;
  char buf[];
};

/**
 * @brief create sds with initlen
 * 
 * @param init 
 * @param initlen 
 * @return sds 
 */
sds sdsnewlen(const void *init, size_t initlen);

/**
 * @brief create sds with default length
 * 
 * @param init 
 * @return sds 
 */
sds sdsnew(const char *init);
sds sdstempty();
size_t sdslen(const sds s);
sds sdsdup(const sds s);
void sdsfree(sds s);
size_t sdsavail(sds s);
sds sdscatlen(sds s, void *t, size_t len);
sds sdscat(sds s, char *t);
sds sdscpylen(sds s, char *t, size_t len);
sds sdscpy(sds s, char *t);
sds sdscatprintf(sds s, const char *fmr, ...);
sds sdstrim(sds s, const char *cset);
sds sdsrange(sds s, long start, long end);
void sdsupdatelen(sds s);
int sdscmp(sds s1, sds s2);
sds *sdssplitlen(char *s, int len, char *sep, int seplen, int *count);
void sdstolower(sds s);

#endif
