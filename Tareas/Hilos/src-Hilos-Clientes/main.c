// Crear un programa que se conecte a un servidor y este haga peticiones diferentes para la busqueda de un archivo 
// El servidor debe crear diferentes hilos para poder atender a varios clientes


// Se van a realizar peticiones randomicas para encontrar la edad, carrera y apellidos de un estudiante dadas
// unas caracteristicas especiales
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <strings.h>

#define NUM_HILOS 16
#define PORT 8080
#define BACKLOG 12
#define serverIP "127.0.0.1"

struct sockaddr_in client; 


int main(){

    int num_peticiones = 0 ;
    int clientfd;
    socklen_t sockaddr_len;
    ssize_t r_send;
    char buffer[16];


    printf("Bienvenido al programa donde usted hará un rol de cliente \n");
    printf("Por favor, ingrese el número de peticiones que quiere realizar \n");

    scanf("%d",&num_peticiones);


    printf("Inicio Proceso Cliente\n");

    // Creación de socket
    clientfd = socket(AF_INET, SOCK_STREAM, 0);

    if (clientfd < 0) {
        perror("Error create socket\n");
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

    if (connect(clientfd, (struct sockaddr *) &client, sizeof(struct sockaddr)) < 0) {
        perror("Error conexión servidor");
        exit(-1);
    }

    close(clientfd);

    return 0;
}


