#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

const string NOMBRE_ARCHIVO = "personas.txt";
const char DELIMITADOR = ',';

struct Persona
{
	int edad;
	string nombre;
};

vector<Persona> obtener_personas_de_archivo()
{
	vector<Persona> personas;
	Persona persona;
	ifstream archivo(NOMBRE_ARCHIVO.c_str());
	string linea, edad, nombre;
	while (getline(archivo, linea))
	{
		stringstream input_stringstream(linea);
		getline(input_stringstream, edad, DELIMITADOR);
		getline(input_stringstream, nombre, DELIMITADOR);
		persona.edad = stoi(edad); // Edad es cadena. Asignamos la propiedad según lo que regrese "stoi"
		persona.nombre = nombre;
		personas.push_back(persona);
	}
	return personas;
}

void guardar_personas_en_archivo(vector<Persona> personas)
{
	ofstream archivo;
	archivo.open(NOMBRE_ARCHIVO, fstream::out);
	int i;
	for (i = 0; i < personas.size(); i++)
	{
		Persona persona = personas[i];
		archivo << persona.edad << DELIMITADOR << persona.nombre << "\n";
	}
	archivo.close();
}

void imprimir_personas(vector<Persona> personas)
{

	int i;
	for (i = 0; i < personas.size(); i++)
	{
		Persona persona = personas.at(i);
		cout << "Tenemos a la persona " << persona.nombre << " con edad " << persona.edad << "\n";
	}
}

int main(int argc, char const *argv[])
{
	vector<Persona> personasParaGuardar;
	personasParaGuardar.push_back(Persona{20, "Luis"});
	personasParaGuardar.push_back(Persona{40, "Leon"});
	personasParaGuardar.push_back(Persona{15, "Marijo"});
	personasParaGuardar.push_back(Persona{90, "Chris"});
	guardar_personas_en_archivo(personasParaGuardar);
	// Obtenerlas de nuevo
	vector<Persona> personasLeidasDeArchivo = obtener_personas_de_archivo();
	imprimir_personas(personasLeidasDeArchivo);
	return 0;
}