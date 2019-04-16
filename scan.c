/*************************************************************************
	> File Name: 12.c
	> Author: xyxiao
	> Mail: amoscykl@163.com 
	> Created Time: 2019年04月14日 星期日 19时53分17秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#include<stdlib.h>
#include"md5.h"


extern int Compute_file_md5(const char*file_path,char* md5_str);

void scan_file(char *pdir,int depth,int fd)
{
	DIR *dir=opendir(pdir);
	
	struct dirent *dp;
	struct stat statbuf;
	char *md5_str=(char*)malloc(sizeof(char)*33);
	memset(md5_str,0,33);
	if(dir==NULL)
	{
		puts("can't open dir");
		return ;
	}
	chdir(pdir);
	while((dp=readdir(dir))!=NULL)
	{

		lstat(dp->d_name,&statbuf);

		if(strcmp("proc",dp->d_name)==0||strcmp("sys",dp->d_name)==0||\
				strcmp("dev",dp->d_name)==0||strcmp("src",dp->d_name)==0)
			continue ;
		
		if(S_ISDIR(statbuf.st_mode))
		{
			if(strcmp(".",dp->d_name)==0||strcmp("..",dp->d_name)==0)
				continue;
		//	printf("%*s%s\n",depth,"",dp->d_name);
			scan_file(dp->d_name,depth+4,fd);
		}else
			{
			
			char *buf=(char *)malloc(sizeof(char)*1024);
			memset(buf,'0',1024);	
			strncpy(buf,dp->d_name,strlen(dp->d_name));
			strncpy(buf+strlen(dp->d_name),"    ",4);
			Compute_file_md5(dp->d_name,md5_str);
			strcpy(buf+(strlen(dp->d_name)+4),md5_str);
			strcpy(buf+(strlen(dp->d_name)+4+strlen(md5_str)),"\n");
			int ret=write(fd,buf,strlen(buf));
		//	printf("%*s%s   ",depth,"",dp->d_name);
		//	printf("%s\n",md5_str);
			free(buf);
		}
	}
		chdir("..");
	closedir(dir);
}

int scan_main(char* pathname)
//int main(int argc,char*argv[])
{
	char *string=(char*)malloc(sizeof(char)*1024);
	memset(string,0,1024);

	char *type="md5.txt";
	char *str1=(char*)malloc(24*sizeof(char));
	memset(str1,0,24);
	strcpy(str1,pathname);
	char *str=str1;
	printf("pathname %s\n",pathname);
	char *p;
	p=string;
	str++;
	
	while(*str1!='\0')
	{
		if(*str1=='/')
			*str1='-';
			str1++;
	}
	
	while(*str!='\0')
	{
		*p=*str;
		p++;
		str++;
	}
	while(*type!='\0')
	{
		*p=*type;
		p++;
		type++;
	}
	*p='\0';

	printf("string %s\n",string);
	int fd=open(string,O_RDWR|O_CREAT);
	if (fd<=0)
		return 0;

	printf("fd %d\n",fd);
	scan_file(pathname,0,fd);
	
	free(string);
	close(fd);
	return 0;
}
