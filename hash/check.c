#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{

   	htItem *item[200];
	htInit(item, 200);
	char *buf=(char*)malloc(sizeof(char)*1024);
	char *key_string=(char*)malloc(sizeof(char)*512);
	char *md5_string=(char*)malloc(sizeof(char)*33);
	size_t len=1024;
	if(buf==NULL)
		return -1;

	FILE* stream=fopen("bootmd5.txt","r+");
	if(stream==NULL)
		return -1;
	size_t read;

	memset(buf,0,len);

	memset(key_string,0,512);
	memset(md5_string,0,33);
	int count=0;
	unsigned int num=0;
	char *str=NULL;
	while((read=getline(&buf,&len,stream))!=-1){
		count++;
		
		str=buf;
		while((*buf)!=' ')
		{
			num++;
			buf++;
		}
		buf=str;
		str=NULL;
		strncpy(key_string,buf,num);
		strncpy(md5_string,buf+4+num,32);

		htSet(key_string,md5_string,item);
		num=0;
		memset(buf,0,1024);
		memset(key_string,0,512);
		memset(md5_string,0,33);
	}	
	fclose(stream);

	//print_hashTable(item);

	printf("Geting ....\n");

	count=0;
	FILE* check_stream=fopen("boot.txt","r+");
	while((read=getline(&buf,&len,check_stream))!=-1){
		count++;
		
		str=buf;
		while((*buf)!=' ')
		{
			num++;
			buf++;
		}
		buf=str;
		str=NULL;
		strncpy(key_string,buf,num);
		strcpy(md5_string,buf+4+num);
		
		htItem *tmp=htGet(key_string,item);
		if(tmp==NULL)
			printf("diff fialed\n");
		if(strncmp(md5_string,tmp->md5,32)!=0)
		{
			printf("now done %s %s",key_string,md5_string);
			printf("old done %s %s\n",tmp->key_string,tmp->md5);
		}
		else{
	//	printf("com %d ",strncmp(md5_string,tmp->md5,32));
			}
		num=0;
		memset(buf,0,1024);
		memset(key_string,0,512);
		memset(md5_string,0,33);	
	}

	
	//printf("get done %s %s\n",tmp->key_string,tmp->md5);		

	free(buf);
	free(key_string);
	free(md5_string);
	free(str);	
	return 0;
}
