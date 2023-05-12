#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include "interfaz.h"
#include "search.h"

int* input();
main(){
    // Variables

    key_t key= 456;//llave para la memoria compartida
    int *shm;//puntero a la memoria compartida
    int shmId,r;//identificador de la memoria compartida
    
    //crear espacio de memoria compartida
    
    shmId = shmget(key, 3*sizeof(float), 0666|IPC_CREAT);
    
    if(shmId < 0){ // Error en la creación de memoria compartida
        perror("Error en shmget");
        exit(EXIT_FAILURE);
    }
    
    //Asociar espacio de memoria creada a este proceso

    shm = shmat(shmId, NULL, 0);

    /*Crear dos procesos*/
    __pid_t pid=fork();
    
    if(pid==-1){
        perror("Error en la creación de procesos");
        exit(EXIT_FAILURE);
    }
    else if(pid==0){
        // Se ejecuta la interfaz del programa mandando el puntero de la memoria compartida
        input(shm);

    }else{
        /*Padre*/
        
        while (wait(NULL)!=-1){/*Esperar hasta que el proceso hijo termine su ejecución*/

            // Se ejecuta la busqueda haciendo uso de la memoria compartida con los datos expuestos    
            search(shm);
            
        }
    }
    r = shmdt(shm);  //desasociar espacio de memoria compartida

    return 0;
}