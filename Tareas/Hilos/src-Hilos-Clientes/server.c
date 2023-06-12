#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>


#define PORT 8080
#define BUFFER_SIZE 1024

int main(){
    int server_id,r, client_id; 
    struct sockaddr_in serverAddress, clientAddress; // Conexión a servidor

    // Creación socket

    server_id = socket(AF_INET,SOCK_STREAM,0); 

    if (server_id < 0 ){
        perror("Error creación cliente");
        exit(-1);
    }
    // Configuracion del servidor por medio de BIND

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY; // Escucha cualquier direccion IP
    serverAddress.sin_port = htons(PORT);
    bzero(serverAddress.sin_zero,8);

    r = bind(server_id,(struct sockaddr*)&serverAddress,sizeof(serverAddress));

    if (r < 0 ){
        perror("Error configuración servidor \n");
        exit(-1);
    }
    
    // Creación del listen

    if (listen(server_id, 3) < 0) {
            perror("Error al escuchar por conexiones entrantes");
            exit(EXIT_FAILURE);
        }
        printf("Esperando conexiones entrantes...\n");
        
    // Creación del Accepting

    socklen_t clientAddressLength = sizeof(clientAddress);
    client_id = accept(server_id, (struct sockaddr*)&clientAddress, &clientAddressLength);

    if (client_id < 0) {
        perror("Error al aceptar la conexión del cliente");
        exit(EXIT_FAILURE);
    }

    printf("Cliente conectado: %s:%d\n", inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port));

    
    // Leer los datos de tipo str enviados por el cliente
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer)); // Poner el buffer en 0

    // Leer el primer valor str
    read(client_id, buffer, sizeof(buffer));
    char valor1[BUFFER_SIZE];
    strncpy(valor1, buffer, sizeof(valor1));

    // leer el segundo valor str
    read(client_id, buffer, sizeof(buffer));
    char valor2[BUFFER_SIZE];
    strncpy(valor2, buffer, sizeof(valor1));

    
    printf("Los mensajes leidos fueron:\n");
    printf("Valor 1: %s\n", valor1);
    printf("Valor 2: %s\n", valor2);
    // Creación del send
    


        
    // Cerrar la conexión con el cliente
    close(client_id);

    // Cerrar el socket del servidor
    close(server_id);

    return 0;

}