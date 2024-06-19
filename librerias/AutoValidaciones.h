#ifndef AUTOVALIDACIONES_H_INCLUDED
#define AUTOVALIDACIONES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>



int limiteMarca(char[]);
int limiteModelo(char[]);
int esAnio(int);

int limiteAnio(int);
int anioNoNegativo(int);

int PrecioNoNegativo(float);

int limiteKms(char[]);
int kmsNumerico(char[]);
int kmsNoNegativo(char[]);

int esVendedor(Persona);


#endif // AUTOVALIDACIONES_H_INCLUDED
