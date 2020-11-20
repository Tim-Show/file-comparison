
#include <iostream>

#include "inspection.h"

using namespace inspection;
hashtable filehash(2000);

int datatohash(char* filename)
{
    if(filename==NULL)
        return -1;
    FILE *stream=fopen(filename,"r+");
    if(stream==NULL)
            return -1;

	char *buf=(char*)malloc(sizeof(char)*1024);
	char *key_string=(char*)malloc(sizeof(char)*512);
	char *md5_string=(char*)malloc(sizeof(char)*33);
	size_t len=1024;
	if(buf==NULL||key_string==NULL||md5_string==NULL)
		return -1;

	memset(buf,0,len);

	memset(key_string,0,512);
	memset(md5_string,0,33);
	int read;
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

		filehash.htSet(key_string,md5_string);
		num=0;
		memset(buf,0,1024);
		memset(key_string,0,512);
		memset(md5_string,0,33);
	}	
	free(buf);
	free(key_string);
	free(md5_string);
	free(str);
	fclose(stream);
    return 0;
}


int difffile(char* filename1)
{
	printf("Geting ....\n");
	char *buf=(char*)malloc(sizeof(char)*1024);
	char *key_string=(char*)malloc(sizeof(char)*512);
	char *md5_string=(char*)malloc(sizeof(char)*33);
	int count=0,read=0,num=0;
    char *str=NULL;

	size_t len=1024;
	
    FILE  *stream=fopen(filename1,"r+");
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
		strcpy(md5_string,buf+4+num);
		
		htItem *tmp=filehash.htGet(key_string);
		if(tmp==NULL)
		{	
			printf("old system haven't the %s file\n",key_string);
			return 0;
		};
		if(strncmp(md5_string,tmp->md5_string,32)!=0)
		{
			printf("now done %s %s",key_string,md5_string);
			printf("old done %s %s\n",tmp->key_string,tmp->md5_string);
		}
		else{
			}
		num=0;
		memset(buf,0,1024);
		memset(key_string,0,512);
		memset(md5_string,0,33);	
	}

	fclose(stream);	

	free(buf);
	free(key_string);
	free(md5_string);
	free(str);	
	return 0;
	
}


int main(int argc,char *argv[])
{
	
	if(argc<3)
	{
		printf("input two argc");
		return 0;
    }
    filehash.htInit(300);
    int ret;
        ret=datatohash(argv[1]);

        if(ret !=0)
            cout<<"data to hashtable failed\n";

       ret=difffile(argv[2]);
        if(ret !=0)
            cout<<"file compare diff is failed\n";

    filehash.print_hashTable();



    std::cout << "Hello world" << std::endl;
    return 0;
}

