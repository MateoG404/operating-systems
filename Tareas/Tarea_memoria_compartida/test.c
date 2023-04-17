#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() {
    int shmid;
    key_t key = 5234;
    char *shm;

    // Creamos la memoria compartida
    shmid = shmget(key, 3*sizeof(float), 0666|IPC_CREAT);

    if (shmid == -1) {
        perror("shmgettt");
        exit(1);
    }

    // Adjuntamos la memoria compartida a nuestro proceso
    shm = shmat(shmid, NULL, 0);

    if (shm == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    // Escribimos un mensaje en la memoria compartida desde el proceso padre
    sprintf(shm, "Hola desde el proceso padre");

    // Creamos un proceso hijo
    pid_t pid ;
    pid = fork();

    if (pid == 0) {
        // Proceso hijo lee desde la memoria compartida
        printf("Mensaje del proceso hijo: %s\n", shm);

        // Liberamos la memoria compartida del proceso hijo
        shmdt(shm);
    } else {
        // Esperamos a que el proceso hijo termine
        wait(NULL);

        // Liberamos la memoria compartida del proceso padre
        shmdt(shm);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}
