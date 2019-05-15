
#ifndef _INSPECTION_
#define _INSPECTION_

#include<iostream>
#include <stdlib.h>
#include<memory.h>
#include<stdio.h>
#include<string.h>

#define MAX_SIZE 1001
#define MD5_LEN 33

#pragma once

namespace inspection{
using namespace std;
typedef  struct  _htItem{

    struct _htItem *next;
    char *key_string;
    char *md5_string;
    int fid;
    int key_len;
    int md5_len;

}htItem;


class inspection
{
public:
    inspection() {}
    ~inspection() {}

private:

};

class hashtable{
private:
    htItem *hitem[MAX_SIZE];
	int hash_length;
public:
    hashtable(int size){
        if(size<0){
            cout<<"intpu error\n";
            exit(-1);
        }
        if(size>MAX_SIZE)
            hash_length=MAX_SIZE;
            else
                hash_length=size;
         int ret;
             ret= htInit(hash_length);
             if(ret<0)
                 cout<<"init hash failed\n";

    }
    ~hashtable(){
		cout<<"hash function finish\n";
    }
    int htInit(int length)
    {
      for (int i = 0; i<length; i++){
        hitem[i] = (htItem*)malloc(sizeof(htItem));
		hitem[i]->md5_string =(char *)malloc(MD5_LEN);
		hitem[i]->key_string =(char *)malloc(24);
        memset(hitem[i]->md5_string, 0, MD5_LEN);
		memset(hitem[i]->key_string, 0, 24);
        }
        hitem[0]->fid=hash_length;
        return 0;
    }
    htItem* htGet(char *key){
   	 int i = htIndex(key);
    	htItem *item = hitem[i]->next;
    	
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
uint htSet(char *key, char * md5){
    unsigned int i = htIndex(key);
    htItem *item = hitem[i];
    while (item->next)
    {
    //已经存在的话则直接更新值
        if (strcmp(key, item->next->key_string) == 0){
            item->next->md5_string = md5;
            return 0;
        }
        else{
            item = item->next;
        }
    }
    item->next = (htItem*)malloc(sizeof(htItem));
	item->next->md5_string=(char *)malloc(MD5_LEN);
	item->next->md5_len=32;

	item->next->key_string=(char*)malloc(strlen(key));
	item->next->key_len=strlen(key);

	memset(item->next->key_string,0,strlen(key));
	memset(item->next->md5_string,0,MD5_LEN);

   	strncpy(item->next->md5_string,md5,32);
   	strncpy(item->next->key_string,key,strlen(key));

    item->next->next = NULL;
    return 0;
}
	/** delete one element of hashtable  删除hash值*/
	int htDel(char *key){
		int i = htIndex(key);
		htItem *item = hitem[i];
		while (item->next){
		    if (strcmp(key, item->next->key_string) == 0){
		        htItem *tmp = item->next;
		        item->next = tmp->next;
				free(tmp->md5_string);
		        free(tmp);
		        return 0;
		    }
		    item = item->next;
        }
		return -1;
	}

	/** BKDR hash function  对字符串进行散列，得到一个整数的hash值*/
	int bkdrHash(char *key)
	{
		int seed = 131;
		int hash = 0;
		while (*key != '\n' && *key != 0)
		{
		    hash = hash * seed + (*key++);
		}
		return (hash & 0x7FFFFFFF);
	}

	/** get the index of hash table  根据得到的hash值选择一个槽位置*/
	int htIndex(char *key){
		int hashedKey = bkdrHash(key);
		int length = (hitem[0]->fid - 1);
		return (int)hashedKey % length + 1;
	}

	/** get element number in the hashtable */
	int htLen(){
		int alength = hitem[0]->fid;
		int i, length = 0;
		for (i = 1; i < alength; i++){
		    if (hitem[i]->next) {
		        length++;
		    }
		}
		return length;
	}

	/** get capacity of hashtable */
	int htCapacity()
	{
		return hitem[0]->fid;
	}

	void print_hashTable()
	{
		int length = hitem[0]->fid;
		int i;
		htItem *item;
		for (i = 1; i < length; i++)
		{
		    item = hitem[i]->next;
		    while (item)
		    {
		        printf("%d:%s => %s %d\n", i,item->key_string, item->md5_string,item->key_len);
		        item = item->next;
		    }
		}
	}

};
};
#endif
