#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <error.h>
#include <fcntl.h>

#define PORT 6369
#define MAX_EVENTS 10
#define BUFFER_SIZE 1024
#define TABLE_SIZE 1000

/**
* data entry
*/
typedef struct Entry {
  char *key;
  char *value;
  struct Entry *next;
} Entry;

// hash table
Entry *hashTable[TABLE_SIZE];

/** hash function */
unsigned int hash(const char *key) {

}
