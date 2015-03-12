/*************************************************************************
  > File Name: client.cpp
  > Author: fgcmaster
  > Mail: fgcmaster@163.com 
  > Created Time: 2015年03月12日 星期四 15时28分12秒
 ************************************************************************/
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sstream>

#define MAXSIZE     1024
#define SERV_PORT   8787
#define FDSIZE        1024
#define EPOLLEVENTS 20

void handle_connection(int sockfd);
void
handle_events(int epollfd,struct epoll_event *events,int num,int sockfd,char *buf);
static void do_read(int epollfd,int fd,int sockfd,char *buf);
static void do_read(int epollfd,int fd,int sockfd,char *buf);
static void do_write(int epollfd,int fd,int sockfd,char *buf);
static void add_event(int epollfd,int fd,int state);
static void delete_event(int epollfd,int fd,int state);
static void modify_event(int epollfd,int fd,int state);

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
			printf(" connect error %d  %s\n", rtn, strerror(errno));
			sleep(3);
		}
		else
		{
			return sockfd;
		}
	}
}

int main(int argc,char *argv[])
{
	while(1)
	{
		int sockfd = tryConnectServer();
		handle_connection(sockfd);
	}
	return 0;
}


void handle_connection(int sockfd)
{
	int epollfd;
	struct epoll_event events[EPOLLEVENTS];
	char buf[MAXSIZE];
	int ret;
	epollfd = epoll_create(FDSIZE);
	add_event(epollfd, sockfd, EPOLLIN);
	//add_event(epollfd,STDIN_FILENO,EPOLLIN);
	write(sockfd, "1", 2);

	for ( ; ; )
	{
		ret = epoll_wait(epollfd,events,EPOLLEVENTS,-1);
		if(ret <= 0)
		{
			printf("epoll_wait error occured %d, %s\n", ret, strerror(errno));
			break;
		}
		handle_events(epollfd,events,ret,sockfd,buf);
	}
	close(epollfd);
}

	void
handle_events(int epollfd,struct epoll_event *events,int num,int sockfd,char *buf)
{
	int fd;
	int i;
	for (i = 0;i < num;i++)
	{
		fd = events[i].data.fd;
		if (events[i].events & EPOLLIN)
			do_read(epollfd,fd,sockfd,buf);
		else if (events[i].events & EPOLLOUT)
			do_write(epollfd,fd,sockfd,buf);
	}
}

static void do_read(int epollfd,int fd,int sockfd,char *buf)
{
	int nread;
	nread = read(fd,buf,MAXSIZE);
	if (nread == -1)
	{
		perror("read error:");
		close(fd);
	}
	else if (nread == 0)
	{
		fprintf(stderr,"server close.\n");
		close(fd);
	}
	else
	{
		std::ostringstream oss;
		oss << atoi(buf) + 1;
		const char* rtnNum = oss.str().c_str();
		printf("%s\n", buf);
		write(fd, rtnNum, strlen(rtnNum));
		sleep(2);
	}
}

static void do_write(int epollfd,int fd,int sockfd,char *buf)
{
	int nwrite;
	nwrite = write(fd,buf,strlen(buf));
	if (nwrite == -1)
	{
		perror("write error:");
		close(fd);
	}
	else
	{
	}
	memset(buf,0,MAXSIZE);
}

static void add_event(int epollfd,int fd,int state)
{
	struct epoll_event ev;
	ev.events = state;
	ev.data.fd = fd;
	epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&ev);
}

static void delete_event(int epollfd,int fd,int state)
{
	struct epoll_event ev;
	ev.events = state;
	ev.data.fd = fd;
	epoll_ctl(epollfd,EPOLL_CTL_DEL,fd,&ev);
}

static void modify_event(int epollfd,int fd,int state)
{
	struct epoll_event ev;
	ev.events = state;
	ev.data.fd = fd;
	epoll_ctl(epollfd,EPOLL_CTL_MOD,fd,&ev);
}

