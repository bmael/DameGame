#include "client.h"


void init_host(hostent * ptr_host, char * host, sockaddr_in *local_addr){

    if((ptr_host = gethostbyname(host)) == NULL ){
            perror("[init_host] : can't find the server with the given host");
            exit(1);
        }
        bcopy((char*)ptr_host->h_addr, (char*)&local_addr->sin_addr, ptr_host->h_length);
        local_addr->sin_family = AF_INET; // or ptr_host->h_addrtype;
}

void assign_port(sockaddr_in *local_addr, int port){
    local_addr->sin_port = htons(port);
}

void create_socket(int * socket_descriptor){
    if((*socket_descriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("[create_socket] : Can't create the connection server socket.");
        exit(1);
    }
}

void server_connection(int socket_descriptor, sockaddr_in local_addr){
    if(connect(socket_descriptor, (sockaddr*)(&local_addr), sizeof(local_addr)) < 0){
        perror("[server_connection] : can't establish a connection with the server");
        exit(1);
    }
}

void server_disconnection(int socket_descriptor){
    close(socket_descriptor);
}
