
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define NUM_HILOS 16

// Estructura de dato
struct datos{

    int a ; 
    char b ; 

};

// Función para cargar los hilos
int carga(){
    double x;
    int i;
    for(i=0; i < 1e09; i++)
        x = x + sin(i);
};
// Función que va a ejecutar el Hilo

void * funcion(void *datos)
{
    struct datos *datosH;
    datosH = datos;
    printf("\na = %i  b = %c", datosH->a, datosH->b);
    fflush(stdout);
    carga();
}


int main()
{

    pthread_t hilo[NUM_HILOS]; // Guarda los identificadores de hilos
    struct datos datosh[NUM_HILOS]; // Arreglo de struct datos
    int r, *rh0;
    // Creación de hilos
    for (int i = 0 ; i < NUM_HILOS ; i ++){

        datosh[i].a = i ;  // Número de hilo
        datosh[i].b = 'A' + i ;

    }

    for(int i = 0; i < NUM_HILOS; i++){   
        r = pthread_create(&hilo[i], NULL, (void *)funcion, (void *)&datosh[i]); // ejecución de hilo
        if(r != 0)
        {
            perror("\n-->pthread_create error: ");
            exit(-1);
        }
    }

    // Espera a que el hilo finalice
    
    for(int i = 0; i < NUM_HILOS; i++)
    {
        r = pthread_join(hilo[i], (void **)&rh0);
        if(r != 0)
        {
            perror("\n-->pthread_join error: ");
            exit(-1);
        }
    }

    return 0;
}
