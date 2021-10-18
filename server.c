#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
    // init socket interface
    int server_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // create a struct to save server information
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));  
    server_addr.sin_family = AF_INET;  
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(65535); 
    // bind the server information
    bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // start listen 
    listen(server_sock, 20);

    // create a buffer to save receive message
    char receiveMessage[64];
    // create a struct to save client information
    struct sockaddr_in client_addr;
    socklen_t client_addr_size = sizeof(client_addr);
    // using infinity loop to keep listening
    while(1){
    // accept connection form client
    int client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_addr_size);

    // send a message to client
    send(client_sock, "client success to connect\n", 64,0);
    // receive a message from client
    recv(client_sock, receiveMessage, sizeof(receiveMessage),0);
    // print receive message
    printf("%s\n",receiveMessage);
    // init print message for them to show immediately.
    fflush(stdout);
    send(client_sock, "got message!", 64, 0);
    }

    return 0;
}