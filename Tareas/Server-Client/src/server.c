#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>


#define PORT 8080

int main(){
    
    int server_id,r, client_id; 
    struct sockaddr_in serverAddress, clientAddress; // Conexión a servidor


    // Creación del socket

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


    // Creación listen
    // Escuchar por conexiones entrantes máximo 3 en pila

    if (listen(server_id, 3) < 0) {
        perror("Error al escuchar por conexiones entrantes");
        exit(EXIT_FAILURE);
    }
    printf("Esperando conexiones entrantes...\n");
    
    // Creación Accept

    // Aceptar conexiones de clientes

    socklen_t clientAddressLength = sizeof(clientAddress);
    client_id = accept(server_id, (struct sockaddr*)&clientAddress, &clientAddressLength);

    if (client_id < 0) {
        perror("Error al aceptar la conexión del cliente");
        exit(EXIT_FAILURE);
    }

    printf("Cliente conectado: %s:%d\n", inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port));

    // Enviar datos al cliente
    char message[1024];
    strcpy(message,"HOLA CLIENTE :");
    strcat(message, inet_ntoa(clientAddress.sin_addr));

    // Creación Send 

    if (send(client_id, message, strlen(message), 0) < 0) {
        perror("Error al enviar datos al cliente");
        exit(EXIT_FAILURE);
    }
    
    // Cerrar la conexión con el cliente
    close(client_id);

    // Cerrar el socket del servidor
    close(server_id);

    return 0;
}
 