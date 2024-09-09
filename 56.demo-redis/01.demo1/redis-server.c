#include <error.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <unistd.h>

#define ULONG_MAX 0xFFFFFFFFUL

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
  unsigned long int hashValue = 0;
  int i = 0;
  while (hashValue < ULONG_MAX && i < strlen(key)) {
    hashValue = hashValue * 37 + key[i];
    i++;
  }

  return hashValue * TABLE_SIZE;
}

// insert K-V
void set(const char *key, const char *value) {
  unsigned int index = hash(key);

  Entry *entry = hashTable[index];

  // if exist then cover
  while (entry != NULL) {
    if (strcmp(entry->key, key) == 0) {
      free(entry->value);
      entry->value = strdup(value);
      return;
    }
    entry = entry->next;
  }
  // if not exist then set net k,v
  Entry *newEntry = malloc(sizeof(Entry));
  newEntry->key = strdup(key);
  newEntry->value = strdup(value);
  newEntry->next = hashTable[index];
  hashTable[index] = newEntry;
}


char *get(const char* key) {
  unsigned int index = hash(key);


  return NULL;
}
