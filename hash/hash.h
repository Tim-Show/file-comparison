#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>
#define HASH_TABLE_CAPACITY 20

typedef char*  string;

/** hash table element*/
typedef struct _htItem{
    struct _htItem  *next;
    char *key_string;
    string md5;

} htItem;

/** init the hashTable 构造函数，申请哈希表的空间*/
void htInit(htItem **ht, int length);

/** set hashTable element 哈希表中插入一个值*/
string htSet(char *key, uint val, htItem **ht);

/** get element from hashtable 从哈希表中获得一个对应的key*/
htItem* htGet(char *key, htItem **ht);

/** Delete element from hashTable 从哈希表中删除一个key*/
int htDel(char *key, htItem **ht);

/** BKDR hash function 对string进行散列得到一个整数值*/
unsigned int bkdrHash(char *key);

/** get the index of hash table 根据key计算一个整数值，然后获得对应的槽位*/
unsigned int htIndex(char *key, htItem **ht);

/** get hashTable elements */
unsigned int htLen(htItem **ht);

/*打印哈希表*/
void print_hashTable(htItem **ht);
#endif
