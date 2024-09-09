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
#define TABLE_SIZE 1024

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

char *get(const char *key) {
  unsigned int index = hash(key);
  Entry *entry = hashTable[index];

  while (entry != NULL) {
    if (strcmp(key, entry->key) == 0) {
      return entry->value;
    }
  }

  return NULL;
}

void delete(const char *key) {
  unsigned int index = hash(key);

  Entry *entry = hashTable[index];
  Entry *prev = NULL;

  while (entry != NULL) {
    if (strcmp(key, entry->key) == 0) {
      if (prev == NULL) {
        hashTable[index] = entry->next;
      } else {
        prev->next = entry->next;
      }
      free(entry->key);
      free(entry->value);
      free(entry);

      return;
    }

    prev = entry;
    entry = entry->next;
  }
}

// set no block
int set_nonblocking(int sockfd) {
  // get old
  int flags = fcntl(sockfd, F_GETFL, 0);

  if (flags == -1)
    return -1;
  flags = flags | O_NONBLOCK;

  return fcntl(sockfd, F_SETFL, flags);
}

// handle client request
void handle_client_request(int client_fd) {
  char buffer[BUFFER_SIZE];

  bzero(buffer, BUFFER_SIZE);

  ssize_t n = read(client_fd, buffer, BUFFER_SIZE - 1);

  if (n <= 0) {
    if (n < 0) {
      perror("read");
      close(client_fd);
      return;
    }
  }
}
