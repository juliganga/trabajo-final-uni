#ifndef PATENTE_H_INCLUDED
#define PATENTE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
typedef struct {
char letras[4];
char numeros[4];
} Patente;



Patente cargarPatente();

void letrasMayus(char[]);

//agregar validacion patente no puede estar duplicada
// letras no pueden ser numeros
//numero no pueden ser letras

#endif // PATENTE_H_INCLUDED
