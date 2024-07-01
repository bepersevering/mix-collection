#include <stdio.h>
#include "hash_table.h"

int main() {
  HashTable* table = create_table();
  insert(table, "apple", "5");
  insert(table, "banana", "3");
  insert(table, "orange", "7");
  insert(table, "mongo", "21");

  printf("Value of 'apple': %s\n", find(table, "apple"));
  printf("Value of 'banana': %s\n", find(table, "banana"));

  erase(table, "apple");
  printf("Value of 'apple': %s\n", find(table, "apple"));

  free_table(table);

  return 0;
}
