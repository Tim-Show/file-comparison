#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void error_handling(char *message);

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char* argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
    char buf[512]={0};
    int str_len=0;
    int read_len=0;

	if(argc<2)
	{
		printf("./client filename");
		return 0;
	}
	
	int fd=0;
	fd=open(argv[1],O_RDWR);
	if(fd<0)
	{
		printf("open file %s faild\n",argv[1]);
		return 0;
	}

    sock=socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    serv_addr.sin_port=htons(atoi("8888"));

    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
        error_handling("connect() error!");

    while(1)
    {
		read_len=read(fd,buf, sizeof(buf)-1);
		
        if(read_len<=0)
			break;
		write(sock,buf,sizeof(buf)-1);
		memset(buf,0,sizeof(buf));
		
		read(sock,buf,sizeof(buf)-1);		
			printf("%s",buf);	
		memset(buf,0,sizeof(buf));
    }
	close(fd);
    close(sock);
    return 0;
}
