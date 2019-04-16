#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
	char *buf=(char*)malloc(sizeof(char)*1024);
	size_t len=1024;
	if(buf==NULL)
		return -1;

	FILE* stream=fopen("./bootmd5.txt",O_RDONLY);
	if(stream==NULL)
		return -1;
	size_t read;

	memset(buf,'\0',len);
	int count=0;
	int num=0;
	while((read=getline(buf,&len,stream))!=-1){
		count++;
		printf("%d: %s\n",count,buf);
		
	}	

    htItem *item[300];
    htInit(item, 300);
	

		
		

}
