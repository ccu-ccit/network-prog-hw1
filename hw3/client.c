#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

const int SERV_PORT = 65535;
const int MAXLINE = 2048;
//使用sentto()傳送資料，使用recvfrom()進入等待狀態，直到接收到server程式傳送的資料，就處理收到的資料。
void dg_cli(FILE *fp , int sockfd , const struct sockaddr *pservaddr , socklen_t servlen)
{
	int n;
	char sendline[MAXLINE] , recvline[MAXLINE+1];
	
	while(fgets(sendline , MAXLINE , fp) != NULL)
	{
		if(sendto(sockfd , sendline , strlen(sendline) , 0 , pservaddr ,  servlen) < 0)
		{
			perror("sendto error");
			exit(1);
		}

		if( ( n = recvfrom(sockfd , recvline , MAXLINE , 0 , NULL , NULL)) < 0)
		{
			perror("recvfrom error");
			exit(1);
		}

		recvline[n] = '\0';
		fputs(recvline , stdout);

	}
}

int main(void)
{
	int sockfd , t;
	struct sockaddr_in servaddr;
	//初始化sockaddr_in結構的變數，並賦值
	bzero(&servaddr , sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	if((t = inet_pton(AF_INET , "127.0.0.1", &servaddr.sin_addr)) <= 0)
	{
		perror("inet_pton error");
		exit(1);
	}
	//使用socket()來建立一個UDP socket，第二個引數為SOCK_DGRAM
	if((sockfd = socket(AF_INET , SOCK_DGRAM , 0)) < 0)
	{
		perror("socket error");
		exit(1);
	}
	//進入無限迴圈程式，dg_cli
	dg_cli(stdin , sockfd , (struct sockaddr *)&servaddr , sizeof(servaddr)) ;
	exit(0);
} 
