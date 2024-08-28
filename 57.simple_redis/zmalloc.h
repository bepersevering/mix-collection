#ifndef __ZMALLOC_H
#define __ZMALLOC_H

#include <stddef.h>
/**
 * @brief 内存分配
 * 
 * @param size 
 * @return void* 
 */
void *zmalloc(size_t size); 
/**
 * @brief 内存再分配
 * 
 * @param ptr 
 * @param size 
 * @return void* 
 */
void *zrealloc(void *ptr, size_t size);
/**
 * @brief 释放内存
 * 
 * @param ptr 
 */
void zfree(void *ptr);
/**
 * @brief copy string
 * 
 * @param s 
 * @return char* 
 */
char *zstrdup(const char *s);
/**
 * @brief show used memory
 * 
 * @return size_t 
 */
size_t zmalloc_used_memory(void);

#endif /* __ZMALLOC_H */
