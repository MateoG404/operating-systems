
// Se creara un archivo que realicé calculo de la serie de Taylor para un e^x
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>

#define NUM_HILOS 4

sem_t *semaforo;

struct Argumentos {
    int valor;
};

void *calculo(void *arg)
{
    struct Argumentos *args = (struct Argumentos *)arg;
    int value = args->valor;

    sem_wait(semaforo); // Poner semaforo en rojo

    //printf("Hilo %d: Inicio de sincronización de procesos\n", value);

    for (int i = 0; i < 5; i++) {
        printf("Hilo %d: -> %d\n", value, value);
    }

    fflush(stdout);
    sleep(2);

    for (int i = 0; i < 5; i++) {
        printf("Hilo %d: ---\n", value);
    }

    fflush(stdout);
    sem_post(semaforo);
    
}

int main()
{
    semaforo = sem_open("semaforo_name", O_CREAT, 0700, 1);

    if (semaforo == SEM_FAILED) {
        perror("Error al crear el semáforo");
        exit(EXIT_FAILURE);
    }

    pthread_t hilos[NUM_HILOS];
    struct Argumentos args[NUM_HILOS];

    printf("Inicio de sincronización de procesos\n");

    for (int i = 0; i < NUM_HILOS; i++) {
        args[i].valor = i + 1;

        int resultado = pthread_create(&hilos[i], NULL, calculo, (void *)&args[i]);
        if (resultado != 0) {
            perror("Error creación hilo");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < NUM_HILOS; i++) {
        pthread_join(hilos[i], NULL);
    }

    sem_close(semaforo);
    sem_unlink("semaforo_name");

    printf("Finalizó\n");
    return 0;
}
