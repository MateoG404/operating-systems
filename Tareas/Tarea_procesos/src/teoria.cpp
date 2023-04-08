#include <iostream>
#include <unistd.h>


using namespace std;
int var = 10 ;
int main(int argc, char *argv[])
{
    pid_t pidC ; // PID del hijo 

    cout << "Incio del programa!"<<endl ;

    cout << "El PID del padre es "<< getpid()<< endl ;

    // Creación de un hijo
    pidC = fork();


    // Loop para ver como se ejecutan

    while(1){
        sleep(3);
        if (pidC > 0 ){
            
            var = 10 ;
            cout << "Se esta ejecutando el padre con un PID de " << getpid() << " Variable " << var <<endl;
            
        }else if (pidC == 0 ){
            var = 15;
            cout << "Se esta ejecutando el hijo con un PID de "<< getpid() << " Variable " << var <<endl;
        
        }else{
            cout << "Error en la creación" <<endl;
        }
            cout << " "<<endl;
        }
}
