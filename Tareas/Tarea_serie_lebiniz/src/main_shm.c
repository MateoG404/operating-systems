// Programa creado para calcular el valor de pi para valores de 10 cifras y más

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    key_t key=1234;
    int shmId,n;
    float  *ap;


    //crear espacio de memoria compartida
    shmId = shmget(key, 3*sizeof(double), 0666|IPC_CREAT);

    //asociar espacio de memoria creada a este proceso
    ap = (float *)shmat(shmId, 0, 0);


    printf(" Ingrese el valor de n para realizar el cálculo de PI \n");
    scanf("%d",&n);

    printf("Padre %i \n",getpid());
    *(ap) = 0 ;
    if(shmId < 0){
        perror("Error en shmget");
        exit(-1);
    }

    // Creación de procesos

    for(int i = 1 ; i <= 4 ; i++){ // Creación de procesos hijos

        pid = fork();

        if (pid == -1){ // Error creación proceso hijo
            perror("Creacion proceso hijo");
            exit(-1);
        }
        else if(pid == 0){ // Proceso hijo

            printf("Se esta ejecutando el proceso hijo %d \n",getpid());

            int m = (n/4)*i; // Tamaño max para realizar calculo de pi
            int j = (n/4) * (i-1); // Tamaño inicio para realizar calculo de pi
            
            double val_cal = 0 ;
           
            printf("Valor m %d, valor j %d \n",m,j);
           
            for ( j ; j <= m; ++j){
                val_cal += (pow(-1, j) )/ (2 * j + 1);
            }

            // Guardado de valor calculado en la memoria compartida
            printf("Valor calculado %f \n",val_cal);
            *(ap) = (val_cal + *(ap));

            return 0;
        }
    }

    // Esperar a que todos los procesos hijos terminen
    for (int i = 1; i <= 4; i++)
    {
        wait(NULL);
    }

    // Imprimir el valor de pi
    printf("El valor de pi es: %f\n", *(ap));

    // Liberar la memoria compartida
    shmdt(ap);
    shmctl(shmId, IPC_RMID, NULL);

    return 0;

}
