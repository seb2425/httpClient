#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>


int main(){

    //load data to serve
    FILE* html_data;
    html_data= fopen("index.html", "r");

    //create it to a   response
    char response_data[1024];
    fgets(response_data,sizeof(response_data),html_data);

    //add the html header , this will vary
    char http_resp[2048]= "hido HTTP/1.1 200 hido OK \r\n\n";
    strcat(http_resp,response_data);

    char test[256]= "hidohito";

    //create a socket for connection
    int server_socket=socket(AF_INET,SOCK_STREAM,0);

    //setting a port
    struct sockaddr_in server_address;
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(3000);
    server_address.sin_addr.s_addr=INADDR_ANY;

    //binding our address to the socket
    bind(server_socket,(struct sockaddr*) &server_address, sizeof(server_address));
    //return 0;

    //listen
    int listen_status =listen(server_socket, 5);

    int client_socket;
    while(1){
        client_socket=accept(server_socket,NULL,NULL);
        send(client_socket,http_resp,sizeof(http_resp),0);
        close(client_socket);
    }

    return 0;
    //connect our server socket to out server addres
    //int connection_status= connect(server_socket,(struct sockaddr*)&server_address , sizeof(server_address));

}