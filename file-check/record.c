/*************************************************************************
	> File Name: fork.c
	> Author: xyxiao
	> Mail: amoscykl@163.com 
	> Created Time: 2019年04月15日 星期一 20时19分48秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
extern void scan_file(char* argv[]);
extern void scan_main(char* pathname);


int main(int argc,char *argv[])
{
	int status=0;
	pid_t pid;
	pid_t child[10]={0};
	printf("argc %d\n",argc);
	for(int i=1;i<argc;i++)
	{
		if((status=fork())==0)
		{
			scan_main(argv[i]);
			//exit(0);
			printf("this is chlid %d\n",getpid());
			//sleep(i*10);
			return 0;
		}
	}
	printf("this is parent %d\n",getppid());
	while((pid=wait(&status))>0){
		printf("pid=%d\n ",pid);
	}
}
