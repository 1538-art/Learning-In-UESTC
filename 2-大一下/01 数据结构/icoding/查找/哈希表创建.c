/*哈希表创建
  
  哈希表（Hash Table，也叫散列表），是根据键（Key）而直接访问在内存存储位置的数据结构。
  也就是说，它通过计算一个关于键值的函数，将所需查询的数据映射到表中一个位置来访问记录，
  这加快了查找速度。这个映射函数称做哈希函数，存放记录的数组称做哈希表。哈希表相关定义如下：

typedef enum{
  HASH_OK,
  HASH_ERROR,
  HASH_ADDED,
  HASH_REPLACED_VALUE,
  HASH_ALREADY_ADDED,
  HASH_DELETED,
  HASH_NOT_FOUND,
} HASH_RESULT;

typedef struct __HashEntry HashEntry;
struct __HashEntry{
  union{
    char  *str_value;
    double dbl_value;
    int       int_value;
  } key;
  union{
    char  *str_value;
    double dbl_value;
    int       int_value;
    long   long_value;
    void  *ptr_value;
  } value;
  HashEntry *next;
};

struct __HashTable{
  HashEntry **bucket;
  int size;
  HASH_RESULT last_error;
};
typedef struct __HashTable HashTable;

// 创建大小为hash_size的哈希表，创建成功后返回HashTable类型的指针，否则返回NULL。
HashTable *create_hash(int hash_size);

哈希表相关说明：

HASH_RESULT 类型为相关函数的返回类型
HashEntry 为哈希表所保存元素（即键值对 《key, value》）类型
  HashTable 为哈希表，其中 bucket 指向大小为size的、元素类型为 HashEntry*的指针数组
  哈希表采用链地址法处理冲突
请实现 create_hash 函数，创建指定大小的哈希表。
*/
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

HashTable* create_hash(int size){
  HashTable *tb = (HashTable*)malloc(sizeof(HashTable));
  if(tb == NULL){
    return NULL;
  }
  tb->size = size;
  tb->bucket = (HashEntry**)malloc(sizeof(HashEntry*) * size);
  if(tb->bucket == NULL){
    free(tb);
    return NULL;
  }
  for(int i = 0;i < size;++i){
    tb->bucket[i] = NULL;
  }
  tb->last_error = HASH_OK;
  return tb;
}