#ifdef _INTERFAZ_H_
#define _INTERFAZ_H_

int* home();/*imprime la interfaz del homepage*/
void errors(int *value, int left, int right);/*imprime un error en caso de que el usuario ingrese un numero que no corresponda a una opcion*/
void input();/*imprime la interfaz para ingresar los datos de origen, destino y hora*/
#endif