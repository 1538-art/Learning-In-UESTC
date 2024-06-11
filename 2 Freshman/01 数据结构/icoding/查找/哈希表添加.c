/*typedef enum {
  HASH_OK,
  HASH_ERROR,
  HASH_ADDED,
  HASH_REPLACED_VALUE,
  HASH_ALREADY_ADDED,
  HASH_DELETED,
  HASH_NOT_FOUND,
} HASH_RESULT;

typedef struct __HashEntry HashEntry;
struct __HashEntry {
  union {
    char *str_value;
    double dbl_value;
    int int_value;
  } key;
  union {
    char *str_value;
    double dbl_value;
    int int_value;
    long long_value;
    void *ptr_value;
  } value;
  HashEntry *next;
};

struct __HashTable {
  HashEntry **bucket;
  int size;
  HASH_RESULT last_error;
};
typedef struct __HashTable HashTable;

// 向哈希表中添加元素，其中键类型为char*， 元素类型为int。
HASH_RESULT hash_add_int(HashTable *table, const char *key, int value);

//请实现 hash_add_int 函数，向哈希表中添加元素，其中键类型为char*， 元素类型为int。
// 在添加过程中，如果要添加的键值key已在哈希表中，且对应的值value也已存在，
// 则函数返回 HASH_ALREADY_ADDED；如果要添加的键值key已在哈希表中，但对应的
// 值value不同，则函数将value值更新到哈希表中，之后返回 HASH_REPLACED_VALUE；
// 如果要添加的键值key不在哈希表中，则函数创建 HashEntry 类型，并将其加入到哈希表中，
// 且函数返回 HASH_ADDED。本题所用的哈希函数如下：
long hash_string(const char *str) {
  long hash = 5381;
  int c;
  
  while (c = *str++)
    hash = ((hash << 5) + hash) + c; *//* hash * 33 + c *//*
  if (hash < 0)
    hash *= -1;
  return hash;
}*/

#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include "hash.h"

HASH_RESULT hash_add_int(HashTable *table, const char *key, int value) {
  long hash = hash_string(key) % table->size;
  HashEntry *entry = table->bucket[hash];
  while (entry != NULL) {
    if (strcmp(entry->key.str_value, key) == 0) {
      if (entry->value.int_value == value) {
        table->last_error = HASH_ALREADY_ADDED;
        return HASH_ALREADY_ADDED;
      } else {
        entry->value.int_value = value;
        table->last_error = HASH_REPLACED_VALUE;
        return HASH_REPLACED_VALUE;
      }
    }
    entry = entry->next;
  }
  entry = (HashEntry *) malloc(sizeof(HashEntry));
  if (entry == NULL) {
    table->last_error = HASH_ERROR;
    return HASH_ERROR;
  }
  entry->key.str_value = (char *) malloc(strlen(key) + 1);
  if (entry->key.str_value == NULL) {
    free(entry);
    table->last_error = HASH_ERROR;
    return HASH_ERROR;
  }
  strcpy(entry->key.str_value, key);
  entry->value.int_value = value;
  entry->next = table->bucket[hash];
  table->bucket[hash] = entry;
  table->last_error = HASH_ADDED;
  return HASH_ADDED;
}