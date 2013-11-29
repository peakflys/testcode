#include <sys/socket.h>  //listen() send()
#include <sys/types.h>	//这两个头文件包含 socket() bind() connect() accept() recv() sendto() recvfrom()
#include <netinet/in.h> //struct sockaddr_in PROTO_ICMP INADDR_ANY 等结构题的声明和宏定义
#include <arpa/inet.h> //inet_aton inet_addr inet_network等函数的定义
#include <sys/epoll.h> //epoll
#include <errno.h>
#include <assert.h>
#include <fcntl.h> //fcntl()和相应的宏
#include <map>
#include <iostream>
#include <string>

const unsigned int PORT = 6666; 
const unsigned int LISTENNUM = 2000; 
const unsigned int MAXEPOLLSIZE = 10000;
const unsigned int MAXBUF = 100*1024;

static std::map<int,std::vector<std::string> > sendData;
static std::map<int,bool > writeable;

int setnonblocking(int fd)
{
	if(fcntl(fd,F_SETFL,fcntl(fd,F_GETFL,0)|O_NONBLOCK) == -1)
		return -1;
	return 0;
}

int sendCmd(int fd)
{
	if(sendData.find(fd) == sendData.end())
	{
		writeable[fd] = true;
		return 1;
	}
	for(std::vector<std::string> >::iterator it=sendData[fd].begin();it!=sendData[fd].end();)
	{
		std::string data = *it;
		std::cout<<"S->C :"<<data<<std::endl;
		inet ret = ::send(fd,data.c_str(),strlen(data.c_str()),0);
		if(-1 == ret || 0 == ret)
		{
			++it;
			if(EINTR == errno)
				continue;
			if(EAGAIN == errno)
			{
				writeable[fd] = false;
				return 1;
			}
			else
				return 0;
		}
		else
			it = sendData[fd].erase(it);

	}
	return 1;
}

int handleMsg(int fd)
{
	if(sendData.find(fd) != sendData.end())	
		sendCmd(fd);
	char buf[MAXBUF + 1];
	bzero(buf,sizeof(buf));
	int ret = ::recv(fd,buf,MAXBUF,0);
	if(ret > 0)
	{
		std::cout<<"fd:"<<fd<<":"<<buf<<std::endl;
		if(buf[0] = 'q')
		{
			sendData[fd] = "Bye";
			ret = -1;	//主动断开
		}
		else
		{
			sendData[fd] = "Hello guy,if you anwser q it means goodBye";
		}
	}
	return ret;
}

int main()
{
	int fd = socket(AF_INET,SOCK_STREAM,0); //create TCP socket
	if(fd < 0)
	{
		std::cout<<"socket create error"<<__LINE__<<std::endl;
		return -1;
	}
	int optval = 1;
	if(setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,(void *)&optval,sizeof(int)) < 0) //set socket port can rebind;
	{
		std::cout<<"fail to set socket port can rebind"<<__LINE__<<std::endl;
		::close(fd);
		return -1;
	}

	setnonblocking(fd);

	struct sockaddr_in addrClient,addrServer;
	memset(&addrServer,0,sizeof(sockaddr_in));
	addrServer.sin_family = AF_INET; //ipv4  TCP/IP
	addrServer.sin_port = htons(PORT);
	addrServer.sin_addr.s_addr = htonl(INADDR_ANY); //得到的是空地址，表明此程序接受本机所有外来包
	//inet_aton("192.168.1.230",&addrServer.sin_addr); //指定IP
	
	if(::bind(fd,(struct sockaddr *)&addrServer,sizeof(struct sockaddr_in)) < 0)
	{
		std::cout<<"bind error,port :"<< addrServer.sin_port<<std::endl;
		::close(fd);
		return -1;
	}
	if(::listen(fd,LISTENNUM) < 0) //listen LISTENNUM links from socket
	{
		std::cout<<"listen error"<<std::endl;
		::close(fd);
		return -1;
	}

	std::cout<<"server init success!"<<std::endl;

	int kdpfd = epoll_create(MAXEPOLLSIZE);
	assert(-1 != kdpfd);
	struct epoll_event ev;
	ev.events = EPOLLIN | EPOLLET;
	ev.data.fd = fd;
	assert(0 == epoll_ctl(kdpfd,EPOLL_CTL_ADD,fd,&ev));
	
	struct epoll_event events[MAXEPOLLSIZE];
	int curfds = 1;
	while(1)
	{
		int fdNums = epoll_wait(kdpfd,events,curfds,-1);
		if(fdNums > 0)
		{
			for(int pos=0;pos<fdNums;++pos)
			{
				if(events[pos].data.fd == fd)
				{
					socklen_t len = sizeof(struct sockaddr_in); //下面函数第三个参数要求必须是socklen_t*
					int newfd = ::accept(fd,(struct sockaddr *)&addrClient,&len);//注意数据格式和写法
					if(newfd < 0)
					{
						std::cout<<"accept new link error"<<std::endl;
						continue;
					}
					std::cout<<"new link from "<<inet_ntoa(addrClient.sin_addr)<<" "<<ntohs(addrClient.sin_port)<<"/"<<newfd<<std::endl;

					setnonblocking(newfd);

					ev.events = EPOLLIN |EPOLLOUT | EPOLLET;
					ev.data.fd = newfd;
					if(0 != epoll_ctl(kdpfd,EPOLL_CTL_ADD,newfd,&ev))
					{
						::close(newfd);
						std::cout<<"add epoll new link error"<<std::endl;
						continue;
					}

					sendData[newfd] = "Welcom to TZL Server:";

					++curfds;		//add link num
				}
				else if(events[pos].events & EPOLLIN)
				{
					int ret = handleMsg(events[pos].data.fd);
					if(ret < 1 && errno != EAGAIN)
					{
						::close(events[pos].data.fd);
						epoll_ctl(kdpfd,EPOLL_CTL_DEL,events[pos].data.fd,&ev);	//应该可以自动关闭socket的
						--curfds;	//delete link num
					}
				}
				else if(events[pos].events & EPOLLOUT)
				{
					int ret = sendCmd(events[pos].data.fd);	
					if(ret < 1 && errno != EAGAIN)
					{
						::close(events[pos].data.fd);
						epoll_ctl(kdpfd,EPOLL_CTL_DEL,events[pos].data.fd,&ev);	//应该可以自动关闭socket的
						--curfds;	//delete link num
					}
				}
			}
		}
	}

	::close(fd);
	return 0;
}
