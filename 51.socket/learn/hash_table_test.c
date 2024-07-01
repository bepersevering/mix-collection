#include <stdio.h>
#include "hash_table.h"

int main() {
  HashTable* table = create_table();
  insert(table, 5, "apple");
  insert(table, 3, "banana");
  insert(table, 7, "orange");
  insert(table, 21, "mongo");

  printf("Value of 'apple': %s\n", find(table, 5));
  printf("Value of 'banana': %s\n", find(table, 3));

  erase(table, 5);
  printf("Value of 'apple': %s\n", find(table, 5));

  free_table(table);

  return 0;
}
