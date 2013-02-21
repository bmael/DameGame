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

int create_socket(){
    int socket_descriptor;
    if((socket_descriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("[create_socket] : Can't create the connection server socket.");
        exit(1);
    }
    return socket_descriptor;

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



int write_frame(int socket_descriptor, frame *frame, int len)
{
    int nb;
//    struct sockaddr to; /* address to send to */
//    int to_len = sizeof(to); /* length of the address */

//    strcpy(to.sa_data, frame->dest);
//    nb = sendto(socket_descriptor, frame, len, 0, &to, to_len);
    return nb;
}

void write_to_server(int socket_descriptor, frame * f){
    if((write(socket_descriptor, (char*) f, sizeof(frame))) < 0){
        perror("erreur : impossible d'écrire le message destiné au serveur.");
        exit(1);
    }
}


char* read_server_information(int socket_descriptor){
    char buffer[256];
    char * res = "";
    int length;
    if((length = read(socket_descriptor, buffer, sizeof(buffer))) > 0){
        printf("answer of the server : \n");
        memcpy(res,buffer, strlen(buffer));
        //write(1, strcat(buffer, "plop"), length);

    }
    return res;
}
