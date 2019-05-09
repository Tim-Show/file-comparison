#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<string.h>
#include <unistd.h>
#include <sys/wait.h>




int task(int id)
{
	int client_sockfd;
	int len;
	struct sockaddr_in remote_addr; //服务器端网络地址结构体
	char *buf="1234";  //数据传送的缓冲区
	memset(&remote_addr,0,sizeof(remote_addr)); //数据初始化--清零
	remote_addr.sin_family=AF_INET; //设置为IP通信
	remote_addr.sin_addr.s_addr=inet_addr("127.0.0.1");//服务器IP地址
	remote_addr.sin_port=htons(8000); //服务器端口号
	
	/*创建客户端套接字--IPv4协议，面向连接通信，TCP协议*/
	if((client_sockfd=socket(PF_INET,SOCK_STREAM,0))<0)
	{
		perror("socket error");
		return 1;
	}
	
	/*将套接字绑定到服务器的网络地址上*/
	if(connect(client_sockfd,(struct sockaddr *)&remote_addr,sizeof(struct sockaddr))<0)
	{
		perror("connect error");
		return 1;
	}
	printf("connected to server\n");
	
	
	/*循环的发送接收信息并打印接收信息（可以按需发送）--recv返回接收到的字节数，send返回发送的字节数*/

	while(1)
	{
		len=send(client_sockfd,buf,strlen(buf),0);
		sleep(1);
		printf("进程Id %d 发送成功 %s\n",id,buf);
	}
	/*关闭套接字*/
	close(client_sockfd);
    
	return 0;
}

int main()
{
	int status=0;
	pid_t pid;
	for(int i=1;i<10;i++)
	{
		if((status=fork())==0)
		{
			task(i);
			return 0;
		}
	}

	printf("this is parent%d\n",getppid());
	while((pid=wait(&status))>0)
	{
		printf("pid=%d \n",pid);
	}
	
}




