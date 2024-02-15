#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]){
    char *address=argv[1];

    int client_socket=socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in server_address;
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(80);
    //server_address.sin_addr.s_addr=INADDR_ANY;
    if (inet_aton(address, &server_address.sin_addr) == 0) {
        fprintf(stderr, "Invalid address: %s\n", address);
        close(client_socket);
        exit(EXIT_FAILURE);
    }
    //server_address.sin_zero=

    int connection_status=connect(client_socket,(struct sockaddr*)&server_address, sizeof(server_address));

    char request[]="GET / HTTP/1.1\r\n\r\n";
    char response[4096];
    
    send(client_socket,request,sizeof(request),0);

    if (connection_status==-1) {
        printf("connection failed");
    }

    //char server_resp[1024];

    recv(client_socket,&response,sizeof(response),0);
    
    printf("the server sent  %s", response);
    close(client_socket);

    return 0;
}