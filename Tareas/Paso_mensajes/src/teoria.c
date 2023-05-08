/*Prueba con sockets, usando streams para tx y rx*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>		/* netbd.h es necesitada por la estructura hostent ;-) */
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>

#define PORT 3550   	/* El Puerto Abierto del nodo remoto */
#define MAXDATASIZE 100 /* El numero maximo de datos en bytes */



int create_connect_socket(char *addr)
{
	int fd, r;
	struct sockaddr_in input_addr;
	struct sockaddr_in server;
	r = inet_aton(addr, &input_addr.sin_addr);
 	if(r == -1){ 
		perror("inet_aton");
      exit(EXIT_FAILURE);	
	}
	fd = socket(AF_INET, SOCK_STREAM, 0);
   if(fd == -1){  
      printf("socket() error\n");
      exit(EXIT_FAILURE);
   }

	server.sin_family = AF_INET;
   server.sin_port = htons(PORT);  
   server.sin_addr = input_addr.sin_addr;
   bzero(&(server.sin_zero),8);
	r = connect(fd, (struct sockaddr *)&server, sizeof(struct sockaddr));
   if(r == -1){ 
      printf("connect() error\n");
      exit(EXIT_FAILURE);
   }
	return fd;
}


    
int main()
{
   int fd1, numbytes, a, b, r;    
  	void *buf;  
   char o;

	buf = malloc(MAXDATASIZE);
	fd1 = create_connect_socket("127.0.0.1");
	r = send(fd1, "Hola servidor", 13, 0);
	numbytes = recv(fd1,buf,MAXDATASIZE,0);
   if (numbytes == -1){  
      printf("Error en recv() \n");
      exit(-1);
   }
	a = *(int *)buf;
	b = *(int *)(buf + 4);	
   printf("Mensaje del Servidor1: %0x - %0x - %s - %i bytes\n", a, b, (char *)(buf + 16), numbytes); 
   send(fd1,"holitayoyo",10,0);
	close(fd1);
}