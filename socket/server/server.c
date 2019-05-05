/*************************************************************************
	> File Name: server.c
	> Author: xyxiao
	> Mail: amoscykl@163.com 
	> Created Time: 2019年05月02日 星期四 15时49分20秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>


int main(){
	pid_t pid;
	
	//创建套接字
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //将套接字和IP、端口绑定
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    serv_addr.sin_port = htons(1234);  //端口
    bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    //进入监听状态，等待用户发起请求
    listen(serv_sock, 20);

    //接收客户端请求
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
  
	for(;;)
	{
	int client_fd = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);


	if((pid=fork())==0)
	{

		close(serv_sock);
	
	    //向客户端发送数据
		char buff[255]={0};
		
		for(;;)
		{
		int len=read(client_fd,buff,4);
		printf("recv %s  len=%d \n",buff,len);
		
	    write(client_fd,buff, strlen(buff));
		memset(buff,0,sizeof(buff));
		sleep(1);
		}
	    //关闭套接字
	    close(client_fd);
		exit(0);
	}

}
    return 0;
}
