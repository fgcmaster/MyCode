/*************************************************************************
  > File Name: server.cpp
  > Author: fgcmaster 
  > Mail: fgcmaster@163.com 
  > Created Time: 2015年03月10日 星期二 13时25分35秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define PORT        8787
#define MAXLINE     1024
#define LISTENQ     400 

//函数声明
//创建套接字并进行绑定
static int socket_bind(int port);
//IO多路复用select
static void do_select(int listenfd);
//处理多个连接
static void handle_connection(int *connfds,int num,fd_set *prset,fd_set *pallset, int&);

int main(int argc,char *argv[])
{
	int  listenfd,connfd,sockfd;
	struct sockaddr_in cliaddr;
	socklen_t cliaddrlen;
	listenfd = socket_bind(PORT);
	listen(listenfd,LISTENQ);
	do_select(listenfd);
	return 0;
}

static int socket_bind(int port)
{
	int  listenfd;
	struct sockaddr_in servaddr;
	listenfd = socket(AF_INET,SOCK_STREAM,0);
	if (listenfd == -1)
	{
		perror("socket error:");
		exit(1);
	}
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//inet_pton(AF_INET,ip,&servaddr.sin_addr);
	servaddr.sin_port = htons(port);
	//servaddr.sin_addr.s_addr = inet_addr(ip);
	if (bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) == -1)
	{
		perror("bind error: ");
		exit(1);
	}
	return listenfd;
}

static void do_select(int listenfd)
{
	int  connfd,sockfd;
	struct sockaddr_in cliaddr;
	socklen_t cliaddrlen;
	fd_set  rset,allset;
	int maxfd,maxi;
	int i;
	int clientfds[FD_SETSIZE];  //保存客户连接描述符
	int nready;
	//初始化客户连接描述符
	for (i = 0;i < FD_SETSIZE;i++)
		clientfds[i] = -1;
	maxi = -1;
	FD_ZERO(&allset);
	//添加监听描述符
	FD_SET(listenfd,&allset);
	maxfd = listenfd;
	
	int activeSocketNum = 0;
	//循环处理
	for ( ; ; )
	{
		rset = allset;
		//获取可用描述符的个数
		nready = select(maxfd+1,&rset,NULL,NULL,NULL);
		if (nready == -1)
		{
			perror("select error:");
			exit(1);
		}
		//测试监听描述符是否准备好
		if (FD_ISSET(listenfd,&rset))
		{
			cliaddrlen = sizeof(cliaddr);
			//接受新的连接
			if ((connfd = accept(listenfd,(struct sockaddr*)&cliaddr,&cliaddrlen)) == -1)
			{
				if (errno == EINTR)
					continue;
				else
				{
					perror("accept error:");
					exit(1);
				}
			}
			fprintf(stdout,"accept a new client: %s:%d\n", inet_ntoa(cliaddr.sin_addr),cliaddr.sin_port);
			activeSocketNum++;
			//将新的连接描述符添加到数组中
			for (i = 0;i <FD_SETSIZE;i++)
			{
				if (clientfds[i] < 0)
				{
					clientfds[i] = connfd;
					break;
				}
			}
			if (i == FD_SETSIZE)
			{
				fprintf(stderr,"too many clients.\n");
				exit(1);
			}
			//将新的描述符添加到读描述符集合中
			FD_SET(connfd,&allset);
			//write(connfd,"1",2);
			//描述符个数
			maxfd = (connfd > maxfd ? connfd : maxfd);
			//记录客户连接套接字的个数
			maxi = (i > maxi ? i : maxi);
			if (--nready <= 0)
				continue;
		}
		//处理客户连接
	    printf(" current active socket is %d\n", activeSocketNum);
		handle_connection(clientfds,maxi,&rset,&allset, activeSocketNum);
	}
}

static void handle_connection(int *connfds,int num,fd_set *prset,fd_set *pallset, int& activeSocketNum)
{
	int i,n;
	char buf[MAXLINE];
	memset(buf,0,MAXLINE);
	for (i = 0;i <= num;i++)
	{
		if (connfds[i] < 0)
			continue;
		//测试客户描述符是否准备好
		if (FD_ISSET(connfds[i],prset))
		{
			//接收客户端发送的信息
			memset(buf, '\0', MAXLINE);
			n = read(connfds[i],buf,MAXLINE);
			if (n == 0)
			{
				close(connfds[i]);
				FD_CLR(connfds[i],pallset);
				connfds[i] = -1;
				activeSocketNum--;
				continue;
			}
			//printf("%d read msg is: %d  %s\n", connfds[i], n, buf);
			//向客户端发送buf
			write(connfds[i],buf,n);
		}
	}
}
