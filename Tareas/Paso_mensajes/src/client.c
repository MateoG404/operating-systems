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
#define serverIP "127.0.0.1"
#define BACKLOG 12

struct sockaddr_in client; 


int main(){
    // Variables
    
    int clientfd;
    socklen_t sockaddr_len;
    ssize_t r_send ;
    char buffer[16];

    printf("Inicio Proceso Cliente \n");

    // Creación de socket

    clientfd = socket(AF_INET,SOCK_STREAM,0);

    if (clientfd < 0 ){
        perror("Error create socket \n");
        exit(-1);
    }
    
    // Creacion connect
    
    client.sin_family = AF_INET;
    client.sin_port = htons(PORT);
    
    // Convertir dirección IP a formato valido para serverAddress

    if (inet_pton(AF_INET, serverIP, &(client.sin_addr)) < 0 ){
        perror("Error configuracion servidor \n");
        exit(-1);
    }
    // Crear conexión 
    if (connect(clientfd, (struct sockaddr*)&client,(socklen_t)sizeof(struct sockaddr)) < 0){
        perror("Error conexion servidor");
        exit(-1);

    }
    // Recibir mensaje por socket
    int r ;
    r = recv(clientfd,buffer,16,0);
    if (r  < 0){
        perror("Error recibir mensajes");
        exit(-1);
    }
    buffer[r] = 0;

    printf("Mensaje \n");
    printf(buffer);
    
    close(clientfd);
    
}
