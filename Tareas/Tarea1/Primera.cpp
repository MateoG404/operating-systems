/// Tarea ///

/* 1. Reservar una estructura y cargar la estructura
        1. Nombre (string)
        2. Edad (int)
        3. Estatura (float) 
    
    2. Llenar y guardar en un archivo de texto plano y binario la información

    3. Realizar otro programa para que lea ambos archivos y los imprima en pantalla

*/

#include <iostream>
#include <stdio.h>
#include <string.h>

#define max_long 70

using namespace std;

int main()
{
    // Declaración de estructuras
    struct DATO{
        char nombre[max_long] ;
        int edad;
        float estatura;

    }variable;


    cout << "Por favor llene los siguientes campos "<<endl;
    
    cout << "Nombre"<<endl ; cin >> variable.nombre;
    cout << "Edad"<<endl ; cin >> variable.edad;
    cout << "Estatura"<<endl ; cin >> variable.estatura;
    
    // Creación y escritura de archivos 
    

    FILE * archivo;
    char ed = char(variable.edad);

    archivo = fopen("nombre_archivo.txt","w");
    fputs(variable.nombre,archivo);
    ///fputs(ed,archivo);
    //fputs(variable.estatura,archivo);
    fclose(archivo);


    return 0;
}