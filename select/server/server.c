#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<string.h>
#include <unistd.h>
#include<sys/time.h>
#include<sys/types.h>
#include<sys/select.h>


 
int main(int argc, char *argv[])
{
	int server_sockfd;//服务器端套接字
	int clifd;//客户端套接字
	int len;
	struct sockaddr_in my_addr;   //服务器网络地址结构体
	struct sockaddr_in remote_addr; //客户端网络地址结构体
	int sin_size;
	char buf[BUFSIZ];  //数据传送的缓冲区
	memset(&my_addr,0,sizeof(my_addr)); //数据初始化--清零
	my_addr.sin_family=AF_INET; //设置为IP通信
	my_addr.sin_addr.s_addr=INADDR_ANY;//服务器IP地址--允许连接到所有本地地址上
	my_addr.sin_port=htons(8000); //服务器端口号
	
	/*创建服务器端套接字--IPv4协议，面向连接通信，TCP协议*/
	if((server_sockfd=socket(PF_INET,SOCK_STREAM,0))<0)
	{  
		perror("socket error");
		return 1;
	}
 
 
	/*将套接字绑定到服务器的网络地址上*/
	if(bind(server_sockfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr))<0)
	{
		perror("bind error");
		return 1;
	}
	
	/*监听连接请求--监听队列长度为5*/
	if(listen(server_sockfd,5)<0)
	{
		perror("listen error");
		return 1;
	};
	
	sin_size=sizeof(struct sockaddr_in);
	
	fd_set rfds,srfds,wfds;

	int fd[1024];
	for(int i=0;i<1024;i++)
		fd[i]=0;
	int max=0;
	struct timeval tv;
	int retval;
	int count=0;
	FD_ZERO(&rfds);

	
	tv.tv_sec=30;
	tv.tv_usec=0;
	
	FD_SET(server_sockfd,&rfds);
	
	srfds=rfds;

	max=server_sockfd+1;
	/*等待客户端连接请求到达*/
	for(;;){
	rfds=srfds;

	retval=select(max,&rfds,NULL,NULL,&tv);
	if(retval<0){
		perror("select");
		break;
	}else if(retval==0){
	
		tv.tv_sec=60;
		tv.tv_usec=0;
		printf("timeout\n");
		//continue;
	}
		
	if(FD_ISSET(server_sockfd,&rfds)){
		if((clifd=accept(server_sockfd,(struct sockaddr *)&remote_addr,&sin_size))<0)
		{
			perror("accept error");
			//return 1;
		}
		printf("接受新的客服端: %d\n",clifd);
		fd[clifd]=clifd;
		FD_SET(clifd,&srfds);
		max=fd[clifd]+1;
	}
		
		for(int  i=3;i<max;i++)
		{
			if(FD_ISSET(fd[i],&rfds))
			{
				retval=read(fd[i],buf,sizeof(buf));
				if(retval<=0)
				{
					close(fd[i]);
					FD_CLR(fd[i],&srfds);
					fd[i]=0;
				}
				printf("客户端%d : %s\n",fd[i]-3,buf);
				memset(buf,0,sizeof(buf));
				
			}

		}
		
 }//for(;;)
	/*关闭套接字*/
	//close(client_sockfd);
	close(server_sockfd);
    
	return 0;
}
