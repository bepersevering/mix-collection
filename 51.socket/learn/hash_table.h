#ifndef HASH_TABLE_H
#define HASH_TABLE_H

// 定义哈希表的大小
#define TABLE_SIZE 1024

// 链表节点结构
typedef struct Node {
  int key;
  char* value;
  struct Node *next;
} Node;

// 哈希表结构
typedef struct HashTable {
  Node *table[TABLE_SIZE];
} HashTable;

/**
 *
 * 哈希函数
 */
unsigned int hash(const int key);

/**
 * 创建新的节点
 */
Node *create_node(const int key, char* value);

/**
 * 创建哈希表
 */
HashTable* create_table();

/**
 * 插入键值对
 */
void insert(HashTable *table, const int key, char* value);

/**
 * 查找值
 */
char* find(HashTable *table, const int key);

/**
 * 删除键值对
 */
void erase(HashTable *table, const int key);

/**
 *释放内存
 */
void free_table(HashTable *table);

#endif // HASH_TABLE_H
