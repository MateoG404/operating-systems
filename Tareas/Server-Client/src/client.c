#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>


#define PORT 8080
#define serverIP "127.0.0.1"

int main(){

    // Definicion de variables

    int client_fd, r ; //  
    struct sockaddr_in serverAddress;



    printf("Inicio cliente\n");

    // Creacion socket cliente

    client_fd = socket(AF_INET,SOCK_STREAM,0);

    if (client_fd < 0 ){
        perror("Error creacion socket cliente \n");
        exit(-1);
    }
    
    // Configuracion del servidor para el cliente
    
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    
    // Convertir dirección IP a formato valido para serverAddress

    if (inet_pton(AF_INET, serverIP, &(serverAddress.sin_addr)) < 0 ){
        perror("Error configuracion servidor \n");
        exit(-1);
    }


    // Creación conexión cliente al servidor

    if (connect(client_fd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("Error al conectar al servidor");
        exit(EXIT_FAILURE);
    }

    // Recibir datos
    char buffer[32];

    r = recv(client_fd,buffer,sizeof(buffer),0);
    buffer[r] = 0 ;

    printf("Mensaje recibido es :\n%s",buffer);

    // Cerrar la conexión
    close(client_fd);

    printf("Final cliente \n");

    return 0;
}
