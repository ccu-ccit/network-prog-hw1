#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/ip.h>

const int SERV_PORT = 65535;
const int MAXLINE = 2048;

//使用recvfrom()進入等待狀態，直到接收到客戶程式傳送的資料，就處理收到的資料，並向客戶程式傳送反饋。這裡是直接把收到的資料發回給客戶程式。
void dg_echo(int sockfd , struct sockaddr *pcliaddr , socklen_t clilen)
{
	int n;
	socklen_t len;
	char mesg[MAXLINE];

	while(1)
	{
        fflush(stdout);
		len = clilen;
		if((n = recvfrom(sockfd , mesg , MAXLINE , 0 , pcliaddr , &len)) <0)
		{
			perror("recvfrom error");
			exit(1);
		}

		if((n = sendto(sockfd , mesg , n , 0 , pcliaddr , len)) < 0)
		{
			perror("sendto error");
			exit(1);
		}
}
}
int main(void)
{
	int sockfd;
	struct sockaddr_in servaddr , cliaddr;
	//初始化sockaddr_in結構的變數，並賦值
	bzero(&servaddr , sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);
	//使用socket()來建立一個UDP socket，第二個引數為SOCK_DGRAM
	if((sockfd = socket(AF_INET , SOCK_DGRAM , 0)) < 0)
	{
		perror("socket error");
		exit(1);
	}
	//使用bind()把上面的socket和定義的IP地址和埠繫結
	if(bind(sockfd , (struct sockaddr *)&servaddr , sizeof(servaddr)))
	{
		perror("bind error");
		exit(1);
	}
    printf("server start");
	//進入無限迴圈程式，dg_echo
	dg_echo(sockfd , (struct sockaddr *)&cliaddr , sizeof(cliaddr));	
}
