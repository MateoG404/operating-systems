// Crear una tuberia para crear un mensaje de acuerdo a la hora real y enviarlo a un nuevo proceso

#include <iostream>
#include <unistd.h>
#include <typeinfo> 
#include <ctime>
#include <cstring>
#include <string> 



using namespace std;

int main(int argc, char *argv[])
{

    // Variables
    int pipeF[2] ; // Creación de array con los dos descriptores pipeF[0] -> Lectura, pipeF[1] -> Escritura
    int var_pipe ;// Variable de validación de la tuberia 
    time_t now ;
    string message = "Saludos desde ";
    int hour, minutes; 
    const char* buffer ;
    pid_t pid ; 
    
    
    printf("Inicio del programa \n");
    
    // Creación de la tuberia

    var_pipe = pipe(pipeF);

    printf("PID del padre es %i \n",getpid()) ;
    
    // Creación del hijo 

    pid = fork();
    while(0){
        
    }
    if (pid == 0 ){ // Hijo
        
        // Cerramos el descriptor del padre

        close(pipeF[0]);

        printf("PID del hijo es %i\n",getpid()) ;

        // Creación del mensaje 
        time(&now);
        struct tm *local = localtime(&now);
        
        hour = local -> tm_hour;
        minutes = local -> tm_min;
        
        message.append(to_string(hour));
        message.append(" : ");
        message.append(to_string(minutes));
    
        char buffer[message.size() + 1];
        strcpy(buffer,message.c_str());

        write(pipeF[1],buffer,sizeof(buffer));
    
        // Cerramos la tuberia para el descriptor de escritura (hijo)
        close(pipeF[1]);


    }else if (pid > 0){ // Padre

        printf("PID del padre es %i \n",getpid()) ;

        // Cerramos el descriptor del hijo
        close(pipeF[1]);

        // Recibimos el mensaje 

        int r ; // Int que recibe cantidad de bytes del descriptor
        char buffer2[50] ;
        r = read(pipeF[0],buffer2,50);
        
        cout << buffer2 << endl ;

        close(pipeF[0]);

        
        printf("Mensaje del hijo es : %s \n", buffer2);

        
    }else{ // Error en la creación de un subproceso
        perror("error fork");
        exit(-1);
    }


}