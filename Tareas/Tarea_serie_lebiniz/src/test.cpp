#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>

using namespace std;

int main() {
    for (int i = 1; i <= 4; i++) {
        pid_t pid = fork();
        
        if (pid == -1) {
            cout << "Error al crear el proceso hijo #" << i << endl;
            return 1;
        } else if (pid == 0) {
            cout << "Este es el proceso hijo #" << i << ", con PID: " << getpid() << endl;
            return 0;
        }
    }

    cout << "Este es el proceso padre, con PID: " << getpid() << endl;

    for (int i = 0; i < 4; i++) {
        wait(NULL);
    }
    double b = 0 ;
    for(auto i = 25 ; i < 50 ; ++i){
        double a = pow(-1, i) / (2 * i + 1);
        //printf("val_cal %f, j %i \n",a,i);   

        b += a;
        //cout << a <<endl;
    }
    cout << "B ->" << b<< endl;
    return 0;
}