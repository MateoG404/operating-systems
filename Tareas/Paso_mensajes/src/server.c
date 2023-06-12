// Archivo creado para simular el paso de mensajes por medio de un servidor

// El servidor recibe el dia, mes y año que nacio y envia la edad que tiene el cliente

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <strings.h>

#define PORT 3535
#define BACKLOG 12

struct sockaddr_in server,client; 


int main(){
    // Variables
    
    int serverfd, clientfd;
    socklen_t tamano;
    struct sockaddr_in serverAddress, clientAddress; // Conexión a servidor
    ssize_t r_send ;

    printf("Inicio Proceso Servidor \n");

    // Creación de socket

    serverfd = socket(AF_INET,SOCK_STREAM,0);

    if (serverfd < 0 ){
        perror("Error create socket \n");
        exit(-1);
    }

    // Creacion bind

        // Llenado de la estructura server 
    
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;
    bzero(server.sin_zero,8);

    if (bind(serverfd,(struct sockaddr *)&server,sizeof(struct sockaddr)) < 0){
        perror("Error configuracion bind - bind");
        exit(-1);
    }

    // Creacion listen 
    if (listen(serverfd,BACKLOG) < 0 ){
        perror("Error listen \n");
        exit(-1);
    }

    // Creación accept
    socklen_t clientAddressLength = sizeof(clientAddress);
    clientfd = accept(serverfd,(struct sockaddr*)&client,&clientAddressLength  );

    // 
    if (clientfd < 0 ){
        perror("Error accept");
        exit(-1);
    }


    // Creacion de send para enviar mensajes

    r_send = send(clientfd,"HOLA",10,0);
    if (r_send < 0){
        perror("Error envio mensaje");
        exit(-1);
    }

    close(clientfd);

}
