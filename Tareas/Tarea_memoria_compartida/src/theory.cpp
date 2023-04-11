// Este programa se encargara de realizar dos procesos emparentados y enviar
// un número haciendo uso de la memoria compartida

#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>


using namespace std;
    
int main(int argc, char *argv[]){

    printf("Incio del programa \n");

    // Variables 
    pid_t pid ;
    key_t key = 45321 ; 
    int shmId ;

    // Creación del espacio de la memoria compartida

    shmId = shmget(key, 3 * sizeof(float), 0666|IPC_CREAT);

    if (shmId < 0){
        perror(" Error shmget()");
        exit(-1);
    }

    // Una vez creada la memoria compartida es necesario asociarla a un proceso, es decir, que el proceso
    // pueda usar dicho espacio de memoria compartido


    // Para hacer lo anterior se usa el método shmat que nos arroja un puntero que nos indica
    // la dirección de la memoria compartida

    double *ap = (double *)shmat(shmId,0,0);

    // Asignación del valor 2.0 a la memoria compartida

    *ap = 2.0 ; 
    // Creación del proceso hijo

    pid = fork(); 
    
    if ( pid < 0 ){
        perror("Error fork()");
        exit(-1);
    }else if(pid == 0){ // Proceso Hijo
        
        // El proceso hijo  escribirá en la memoria compartida los primeros 3 digitos del número e

        *(ap+1) = 0.718; 

        sleep(4);
    }else{ // Proceso padre
        // El proceso padre escribirá los siguientes 3 digitos del número e 

        // Para ello se debe esperar que el proceso hijo realice su tarea

        int status ;
        *(ap + 2) = 0.281 ; 


        if(wait(&status) == pid){ // Espera hasta que el hijo termine
            printf(" El número que escribio el hijo es %f, el que yo padre escribo es %f y el número final escrito es %f",*(ap+1), *(ap+2), *ap + *(ap+1)+ *(ap+2));
        }
    }

    // Cerrar el uso de la memoria compartida

    int r = shmdt(ap); 

    if (r < 0){
        perror(" Error shmdt()");
        exit(-1);
    }



}
