#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/select.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <sstream>
#include <iostream>
#include <pthread.h>
#include <vector>

#define MAXLINE     1024
#define SERV_PORT   8787

#define MAXTHREADS 1 

#define max(a,b) (a > b) ? a : b

void handle_connection(int sockfd);

int tryConnectServer();

void* doClient(void*);

int main(int argc,char *argv[])
{
	std::vector<pthread_t> threadVec(MAXTHREADS);

	for(int i = 0; i < MAXTHREADS; i++)
	{
		pthread_t threadID;
		int rtn = pthread_create(&threadID, NULL, doClient, (void*)&i);
		if(rtn != 0)
		{
			printf(" create pthread error %s\n", strerror(errno));
			break;
		}
		threadVec[i] = threadID;
		//pthread_join(threadID, NULL);
	}

	for(int i = 0; i < MAXTHREADS; i++)
	{
		pthread_join(threadVec[i], NULL);
	}

	printf(" exit %s\n", strerror(errno));

	//doClient();
	return 0;
}

void* doClient(void* arg)
{
	printf(" doClient %u\n", (unsigned int)pthread_self());
	while(1)
	{
		int sockfd = tryConnectServer();
		handle_connection(sockfd);
	}
}

int tryConnectServer()
{
	int                 sockfd;
	while(1)
	{
		struct sockaddr_in  servaddr;
		sockfd = socket(AF_INET,SOCK_STREAM,0);
		bzero(&servaddr,sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = htons(SERV_PORT);
		//inet_pton(AF_INET,IPADDRESS,&servaddr.sin_addr);
		servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

		int rtn = connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
		if(rtn != 0)
		{
			printf(" return %d, %s\n", rtn, strerror(errno));
			sockfd = -1;
			sleep(1);
		}
		else
		{
			printf(" valid sockfd %d\n", sockfd);
			break;
		}
	}
	return sockfd;
}

void handle_connection(int sockfd)
{
	char    recvline[MAXLINE];
	std::ostringstream iss;
	int     maxfdp,stdineof;
	fd_set  rset;
	int n;
	FD_ZERO(&rset);
	//添加标准输入描述符        
	//FD_SET(STDIN_FILENO,&rset);
	//添加连接描述符
	FD_SET(sockfd,&rset);
	maxfdp = sockfd; //max(STDIN_FILENO,sockfd);

	write(sockfd, "1", 1);
	for (; ;)
	{
		//进行轮询
		select(maxfdp+1,&rset,NULL,NULL,NULL);
		//测试连接套接字是否准备好
		if (FD_ISSET(sockfd,&rset))
		{
			n = read(sockfd,recvline,MAXLINE);
			if (n == 0)
			{
				fprintf(stderr,"client: server is closed.\n");
				//close(sockfd);
				shutdown(sockfd, SHUT_RDWR);
				FD_CLR(sockfd,&rset);
				return;
			}
			write(STDOUT_FILENO,recvline,n);
			printf("\n");
			sleep(1);
			iss.str("");
			iss << (atoi(recvline) + 1);
			const char* num = iss.str().c_str();
			write(sockfd, num, strlen(num)+1);
		}
	}
}
