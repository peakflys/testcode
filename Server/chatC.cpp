#include <sys/socket.h>  //listen() send()
#include <sys/types.h>	//这两个头文件包含 socket() bind() connect() accept() recv() sendto() recvfrom()
#include <netinet/in.h> //struct sockaddr_in PROTO_ICMP INADDR_ANY 等结构题的声明和宏定义
#include <arpa/inet.h> //inet_aton inet_addr inet_network等函数的定义
#include <iostream>

const unsigned int MAXBUFF = 4*1024;

void sendCmd(const int fd,const char *msg)
{
	if(::send(fd,msg,strlen(msg),0) < 0)
	{
		std::cout<<"sendCmd error"<<msg<<std::endl;
	}
}

int main(int argc,char **argv)
{
	if(5 != argc)	
	{
		std::cout<<"格式不正确，语法为: -p [serverPort] -a [serverAddr]"<<std::endl;
		exit(1);
	}
	int serverPort = 0;
	struct sockaddr_in serverAddr;
	memset(&serverAddr,0,sizeof(struct sockaddr_in));
	serverAddr.sin_family = AF_INET;
	for(int i=1; i< argc;++i)
	{
		if(strcmp("-p",argv[i]) == 0)
		{
			serverPort = atoi(argv[i+1]);
			if(serverPort < 0 || serverPort > 65535)
			{
				std::cout<<"端口非法"<<std::endl;
				exit(1);
			}
			serverAddr.sin_port = htons(serverPort);
			continue;
		}
		if(0 == strcmp("-a",argv[i]))
		{
			if(inet_aton(argv[i+1],&serverAddr.sin_addr) == 0)
			{
				std::cout<<"地址不合法"<<std::endl;
				exit(1);
			}
			continue;
		}
	}
	if(0 == serverAddr.sin_port || 0 == serverAddr.sin_addr.s_addr)
	{
		std::cout<<"格式不正确，语法为: -p [serverPort] -a [serverAddr]"<<std::endl;
		exit(1);
	}
	int sock = ::socket(AF_INET,SOCK_STREAM,0);
	if(sock < 0)
	{
		std::cout<<"创建套结字失败"<<std::endl;
		::close(sock);
		exit(1);
	}
	if(::connect(sock,(struct sockaddr *)&serverAddr,sizeof(struct sockaddr)) < 0)
	{
		std::cout<<"connect failed:"<<std::endl;
		::close(sock);
		exit(1);	
	}
	char recvBuf[MAXBUFF+1];
	char sendBuf[MAXBUFF+1];
	while(true)
	{
		bzero(recvBuf,sizeof(recvBuf));
		bzero(sendBuf,sizeof(sendBuf));
		if(::recv(sock,recvBuf,MAXBUFF,0) < 0)	
		{
			std::cout<<"接收数据出错"<<std::endl;
			exit(1);
		}
		std::cout<<inet_ntoa(serverAddr.sin_addr)<<" :"<<recvBuf<<std::endl;
		if(0 == strcmp("Bye",recvBuf))
		{
			std::cout<<"安全退出"<<std::endl;
			break;
		}
		std::cout<<"输入回复的信息:";
		std::cin.getline(sendBuf,MAXBUFF); //三参数
		sendCmd(sock,sendBuf);
	}
	::shutdown(sock,SHUT_RDWR); //完全关闭
	exit(0);
}
