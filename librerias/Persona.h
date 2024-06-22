#ifndef PERSONA_H_INCLUDED
#define PERSONA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "Utiles.h"

/// VARIABLES ///

typedef struct { // 174 Bytes
	char dni[9];
	char nombre[50];
	char telefono[14];
	char direccion[100];
	char rol; //comprador, vendedor o special (para consecionaria ), SE TRADUCE EN RUNTIME
} Persona;

Persona*arreglopersona; // Arreglo dinamico de las personas, se puede leer simplemente llamando su nombre, tratenlo como un arreglo.
int cantidadpersonas; // i Es la posicion final de las personas, tambien define cuanto malloc'ear para el arreglo (n+1) ^

/// FUNCIONALIDAD ///

// MENU DE CARGA DE PERSONAS
void menuCargaPersonas();


// CARGA DE PERSONAS (MEMORIA)
void agregarPersona();
void cargarDNI(Persona*);
void cargarNombre(Persona*);
void cargarTEL(Persona*);
void cargarDIR(Persona*);
void cargarRol(Persona*);
// FIN DE CARGA DE PERSONAS.

// GUARDADO A ARCHIVOS
void guardarPersonaAFile(Persona);
void guardarCambiosPersona(Persona,int);
// INICIO DE MODIFICACION DE PERSONAS

void modificarPersona();
void menuDeModificacionPersona(Persona,int);


//

// MUESTRA DE PERSONAS
void menuVerPersonas(); // MUESTRA LAS DOS OPCIONES, MOSTRAR UNA O TODAS LAS PERSONAS

void mostrarPersonasMenu(); // Muestra todas las personas
void mostrarPersonasFull(); // Muestra todos las personas completamente
void mostrarPersonasMin(); // Muestra todas las personas minimamente

void buscarUnaPersona();

void verPersonaFull(Persona);
void verPersonaMin(Persona);
// FIN DE MUESTRA DE PERSONAS

// VERIFICACIONES
int verificarEnteros(char[]);
int verificarChars(char[]);

int verificarDNI(char[]);
int verificarNombre(char[]);
int verificarDir(char[]);
int verificarRol(char);
int verificarTel(char[]);
// FIN VERIFICACIONES

/// AYUDANTES ///
void pasarAMayus(char*);
void traducirRolCliente(char);
Persona buscarSegunDNI(char[]);
int devolverNumEntrada(char[]); // Segun DNI
int verSiDNINoExiste(char[]); // Verificar asi no hay duplicados.
int archivoExiste(char[]);
int esConsecionaria(char[]);

/// CARGA EN MEMORIA ///
void cargarEnArregloPersonasInit();
void cargarPersonaArreglo(Persona);
void allocarEspacioParaPersona(Persona**);

/// CARGA DE MIEMBRO "CONCESIONARIA" ///
void cargarPersonaConsesioanaria();


/// Matrices ///

void mostrarPersonaOrdenadoSegun();

int ordenarSegunParam(int,int param,char[][param]);
void imprimirSeparador(int);
char * acortarDireccion(char[],int);

/// Menu ///

void mostrarMenuPersonas();

#endif // PERSONA_H_INCLUDED
