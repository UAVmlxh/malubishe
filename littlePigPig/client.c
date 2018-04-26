#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include "client.h"
#include<sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#define EHCO_PORT 17892
#define TEST_IP "127.0.0.1"



//客户端程序

//信息长度为16个字节的，Mes_num , 
//得到一个字节的时间标志
int tcp_init()
{
	int sock_fd;
	struct sockaddr_in serv_addr;

	
	/*创建 socket 
	int socket ( int AddressFamily, int Type, int Protocol)
	
AddressFamily参数指定socket操作中所要解释的网络地址类型，参数为如下之一	
	AF_UNIX  表示操作系统文件路径
	AF_INET  表示Internet网络地址 ipv4
	AF_NS    表示XEROX网络地址

Type参数表明了通信的语义，即通信连接的方式。参数为如下之一
	SOCK_STREAM  提供稳定可靠的连接，并且是双向的通信方式，如TCP
	SOCK_DGRAM   提供无连接的数据报通信，如UDP
	SOCK_RAM     提供该问内部网络协议和网络接口，只有root用户才可以使用这些协议
	
返回值：成功则返回socket描述符，出错则返回-1，可通过errno代码进行查看错误原因
	
	*/
	//sock_fd =socket(AF_INET,SOCK_DGRAM,0);  //UDP
	sock_fd =socket(AF_INET,SOCK_STREAM,0); //TCP
	if(-1==sock_fd)
	{
		 perror("create socket error!!");
		return 1;
	}
	
	
	/* 设置server地址结构 */
	bzero(&serv_addr,sizeof(serv_addr));			//初始化结构占用的内存
	serv_addr.sin_family = AF_INET ;			 //设置地址传输层类型
	serv_addr.sin_port   = htons(EHCO_PORT);		//设置监听端口
	serv_addr.sin_addr.s_addr = inet_addr(TEST_IP); //测试网络数据
	//serv_addr.sin_addr.s_addr = htons(INADDR_ANY);  //设置服务器地址
	bzero(&(serv_addr.sin_zero),8);
	
	/* 连接服务器 
	int connect(int sockfd, const struct sockaddr* serv_addr,socklen_t addrlen)
	返回值：0--成功   -1--失败
	sockfd :标识一个套接字
	serv_addr : 套接字s想要连接的主机地址和端口号
	addrlen : serv_addr缓冲区的长度
	
	成功返回 0 
	失败放回的参数：
	EBADF:  		参数sockfd 非合法socket处理代码
	EFAULT: 		参数sorv_addr指针指向无法存取的内存空间
	ENOTSOCK:		参数sockfd为一文件描述词，非socket
	EISOONN:    	参数sockfd的socket已是连线状态
	ECONNREFUSED:	连线要求被server端拒绝
	ETIMEDOUT:		企图连线的操作超过限定时间仍未有响应
	ENETUNREACH:    无法传送数据包至指定的主机
	EAFNOSUPPORT:  	sockaddr结构的sa_family不正确
	EALREADY:		socket为不可阻断且先前的连接操作还未完成
	*/
	if(-1==connect(sock_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)))
	{
		perror("connect() error!\n");
		close(sock_fd);
		return 1;
	}
	
	return sock_fd;
	
}

//将数据中的字节转化成字符串形式
void chages_b_s(const unsigned char *bNum,unsigned char *sNum,int len)
{
	int i;
    char S_num[3]; 
	
	for(i=0;i<len;i++)
	{
		sprintf(S_num, "%02x" ,bNum[i]);
	    memcpy(&sNum[i*2],S_num,3);
	}
	
}


//Mes_num需要发送16个qtsting（字符串中一个数为2个字节）的数据
//getnum得到装换后的8个字节的数据
//前6个字节有效
unsigned char tcp_getMessage(unsigned char *getnum,int sock_fd)
{
	unsigned char tmp_buf[101];		    //接受的数据长度
	                                    //QT则对应的是16个（0-f）的数字
	int  n;
	int  i;

	
    n=recv(sock_fd,tmp_buf,100,0);//从服务端接收数据
	if(n>0)
    {	
		tmp_buf[100]='\0';

		for(i=0;i<16;i++)
		{
			if(tmp_buf[i] >=0x30)tmp_buf[i] -=0x30;//转换字符串数据的 0-9 
			if(tmp_buf[i] >=0x30)tmp_buf[i]  =(tmp_buf[i]-0x30)+9;//装换字符串数据的 a-f
             
		}
		printf("jieshou:");
		for(i=0;i<8;i=i+2)
		{
			getnum[i/2]= (tmp_buf[i]<<4) | tmp_buf[i+1];
			printf("%x ",getnum[i/2]);
			
		}
		printf("\n");
    }	
	else 
	{
		return 2;  //接受数据失败
	}
	return 1; 
}

int   tcp_sendMessage( unsigned char *Mes_num,int sock_fd)
{
	unsigned char buff[20]; 			//发送的数据长度
	int flag=0;
     
	memcpy(&buff[0],&Mes_num[0],8*sizeof(unsigned char));
	flag=send(sock_fd,buff,8,0);//发送数据给服务器

	return flag;
}
