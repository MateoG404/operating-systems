// Programa creado para calcular el valor de pi para valores de 10 cifras y más


#include <cmath>
#include <iomanip>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main()
{
    // Se tendrán 4 hijos para realizar el cálculo de la serie de Lebiniz para valores de 10 cifras, cada proceso tendra 1/4 del valor de 10 cifras

    // Variables
    
    pid_t pid ;
    int pipeF[4][2];
    int val_pipe ;
    int n ;

    cout << "Ingrese el valor de n" <<endl;
    cin >> n ; 


    if (val_pipe < 0 ){
    
        perror("Error pipe()");
        exit(-1);
     
    }
    
    // Creación de tuberias

    for (auto i = 0 ;i < 4 ; ++i){
        
        val_pipe = pipe(pipeF[i]);
    
    }

    printf("Padre %i \n",getpid());

    for (int i = 1; i <= 4; i++) {

        // Creación de los hijos
        pid = fork();

        if (pid == -1) {
            cout << "Error al crear el proceso hijo #" << i << endl;
            exit(-1);

        } else if (pid == 0) {
            
            cout << "Este es el proceso hijo #" << i << ", con PID: " << getpid() << endl;
            
            // Paso de mensajes en las tuberias

            close(pipeF[i][0]); // cerramos lectura en la tuberia

            int m = (n/4)*i;
            int j = (n/4) * (i-1);
            //printf("Valor j %i, Valor m %i de la parte %i \n",j,m,i);
            double val_cal = 0 ;

            for ( j ; j <= m; ++j){
                
                val_cal += pow(-1, j) / (2 * j + 1);
                //printf("val_cal %f, j %i \n",val_cal,j);   
            }
            // Se envia a la tuberia el valor calculado 
            //cout << "Valor de la " << i << " parte es " << val_cal <<endl;

            write(pipeF[i][1],&val_cal,sizeof(val_cal));
            close(pipeF[i][1]);

            exit(0);
        }



    }

    // Sumatoria final
    double val_fin = 0 ;

    for(auto i = 0 ; i <4 ; ++i)
    {
        // Lectura de las tuberias
        close(pipeF[i][1]);
        double val_cal ;
        read(pipeF[i][0],&val_cal,sizeof(val_cal));
        //cout << "Valor de la " << i << " parte es " << val_cal <<endl;
        val_fin += val_cal;

    }
    ostringstream ss ; 

    ss << fixed << setprecision(50) << val_fin*4;
    string pi = ss.str();

    cout << "El calculo de pi es "<< pi<<endl;

    exit(0);
}

