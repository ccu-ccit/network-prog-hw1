#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(){
    // create socket interface
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    // create a serv_addr struct to save connection information
    struct sockaddr_in serv_addr;
    // garbage disposal
    bzero(&serv_addr, sizeof(serv_addr));  
    // using ipv4
    serv_addr.sin_family = AF_INET;
    // server ip address
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // server port
    serv_addr.sin_port = htons(65535);
    // connection request
    int err = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
   if(err==-1){
       printf("fail to connect server\n");
       return 0;
   }
    // create a buffer to save data from server 
    char buffer[64];
    bzero(buffer, sizeof(buffer));
    recv(sock, buffer, sizeof(buffer), 0);
   
    printf("Message form server: %s\n", buffer);
    
    char message[64];
    char receiveMessage[64];
    bzero(message, sizeof(message));
    bzero(receiveMessage, sizeof(receiveMessage));
    printf("send message to server: ");
    scanf("%s", message);
    // Send a message to server
    send(sock, message, sizeof(message), 0);
    // receive 
    recv(sock, receiveMessage, sizeof(receiveMessage), 0);

    printf("%s\n", receiveMessage);
    // init print message for them to show immediately.
    fflush(stdout);
    // close connection
    close(sock);

    return 0;
}