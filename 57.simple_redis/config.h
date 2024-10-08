#ifndef __CONFIG_H
#define __CONFIG_H

#ifdef __APPLE__
#include <AvailabilityMacros.h>
#endif

/* test for malloc_size() */
#ifdef __APPLE__
#include <malloc.h>
#define HAVE_MALLOC_SIZE 1
#define rdis_malloc_size(p) malloc_size(p)
#endif

/* define redis_fstat to fstat or fstat64() */
#if defined(__APPLE__) && !defined(MAC_OS_X_VERSION_10_6)
#define redis_fstat fstat64
#define redis_stat stat64
#else
#define redis_fstat fstat
#define redis_stat stat
#endif

/* test for backtrace() */
#if defined(__APPLE__) || defined(__linux__)
#define HAVE_BACKTRACE 1
#endif

#endif /* __CONFIG_H */
