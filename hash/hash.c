#include "hash.h"

/*初始化HashTable*/
void htInit(htItem **ht, uint length){
    int i;
    for (i = 0; i<length; i++){
        ht[i] = (htItem*)malloc(sizeof(htItem));
		ht[i]->md5 =(char *)malloc(MD5_LEN);
		ht[i]->key_string =(char *)malloc(24);
        memset(ht[i]->md5, 0, MD5_LEN);
		memset(ht[i]->key_string, 0, 24);
        memset(ht[i], 0, sizeof(htItem));
    }
	ht[0]->fid=length;
}

/** get hashTable elements 进行对应的hash值的搜索，如果找到则返回该节点*/
htItem* htGet(char *key ,htItem **ht){
   	 uint i = htIndex(key, ht);
    	htItem *item = ht[i]->next;
    	
	while (item)
    	{
			//printf("key:%s %s\n",key,item->key_string);
        if (strncmp(key,item->key_string,item->key_len) == 0){
            return item;
        }
        item = item->next;

    }
	
    return NULL;
}

/** set hashTable element 插入新的hash值*/
uint htSet(char *key, string md5, htItem **ht){
    unsigned int i = htIndex(key, ht);
    htItem *item = ht[i];
    while (item->next)
    {
    //已经存在的话则直接更新值
        if (strcmp(key, item->next->key_string) == 0){
            item->next->md5 = md5;
            return 0;
        }
        else{
            item = item->next;
        }
    }
    item->next = (htItem*)malloc(sizeof(htItem));
	item->next->md5=(string)malloc(MD5_LEN);
	item->next->md5_len=32;

	item->next->key_string=(string)malloc(strlen(key));
	item->next->key_len=strlen(key);

	memset(item->next->key_string,0,strlen(key));
	memset(item->next->md5,0,MD5_LEN);

    strncpy(item->next->md5,md5,32);
    strncpy(item->next->key_string,key,strlen(key));

    item->next->next = NULL;
    return 0;
}

/** delete one element of hashtable  删除hash值*/
int htDel(char *key, htItem **ht){
    uint i = htIndex(key, ht);
    htItem *item = ht[i];
    while (item->next){
        if (strcmp(key, item->next->key_string) == 0){
            htItem *tmp = item->next;
            item->next = tmp->next;
			free(tmp->md5);
            free(tmp);
            return 0;
        }
        item = item->next;
    }
    return -1;
}

/** BKDR hash function  对字符串进行散列，得到一个整数的hash值*/
uint bkdrHash(char *key)
{
    uint seed = 131;
    uint hash = 0;
    while (*key != '\n' && *key != 0)
    {
        hash = hash * seed + (*key++);
    }
    return (hash & 0x7FFFFFFF);
}

/** get the index of hash table  根据得到的hash值选择一个槽位置*/
uint htIndex(char *key, htItem **ht){
    uint hashedKey = bkdrHash(key);
    uint length = (ht[0]->fid - 1);
    return (uint)hashedKey % length + 1;
}

/** get element number in the hashtable */
uint htLen(htItem **ht){
    uint alength = ht[0]->fid;
    uint i, length = 0;
    for (i = 1; i < alength; i++){
        if (ht[i]->next) {
            length++;
        }
    }
    return length;
}

/** get capacity of hashtable */
uint htCapacity(htItem **ht)
{
    return ht[0]->fid;
}

void print_hashTable(htItem **ht)
{
    uint length = ht[0]->fid;
    uint i;
    htItem *item;
    for (i = 1; i < length; i++)
    {
        item = ht[i]->next;
        while (item)
        {
            printf("%d:%s => %s %d\n", i,item->key_string, item->md5,item->key_len);
            item = item->next;
        }
    }
}
