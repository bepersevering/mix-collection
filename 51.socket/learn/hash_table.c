#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "hash_table.h"


unsigned int hash(const int key) {
  unsigned int hash = 0;
  hash = abs(key);

  return hash % TABLE_SIZE;
}

Node* create_node(const int key, char* value) {
  Node *new_node = (Node*)malloc(sizeof(Node));
  new_node->key = key;
  new_node->value = value;
  new_node->next = NULL;
  return new_node;
}

HashTable* create_table() {
  HashTable *table = (HashTable*)malloc(sizeof(HashTable));
  for (int i = 0; i < TABLE_SIZE; i++) {
    table->table[i] = NULL;
  }

  return table;
}

void insert(HashTable *table, const int key,char* value) {
  unsigned int index = hash(key);
  Node* new_node = create_node(key, value);

  if (table->table[index] == NULL) {
    table->table[index] = new_node;
  } else {
    Node* current = table->table[index];
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = new_node;
  }
}

char* find(HashTable *table, const int key) {
  unsigned index = hash(key);
  Node* current = table->table[index];
  while (current != NULL) {
    if (current->key ==  key) {
      return current->value;
    }
    current = current->next;
  }

  // 表示没找到
  return NULL;
}

void erase(HashTable *table, const int key) {
  unsigned int index = hash(key);
  Node* current = table->table[index];
  Node* prev = NULL;

  while (current != NULL && current->key == key) {
    prev = current;
    current = current->next;
  }

  if (current == NULL) {
    return;
  }

  if (prev == NULL) {
    // 删除第一个节点
    table->table[index] = current->next;
  } else {
    // 删除中间或最后的节点
    prev->next = current->next;
  }

  free(current->value);
  free(current);
}

void free_table(HashTable* table) {
  for (int i = 0; i < TABLE_SIZE; i++) {
    Node* current = table->table[i];
    while (current != NULL) {
      Node* temp = current;
      current = current->next;
      free(temp->value);
    }
  }
}
