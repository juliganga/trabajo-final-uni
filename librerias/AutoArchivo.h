#ifndef AUTOARCHIVO_H_INCLUDED
#define AUTOARCHIVO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "Patente.h"
#include "Auto.h"
#include "Persona.h"

/** Constante con el nombre de archivo, para persistir los usuarios **/
#define ARCHIVO_AUTOS "AutoArchivo.bin"

/**
    Definicion de tipo.
**/
typedef struct {
    Patente patente;
    char marca[15];
    char modelo[15];
    int anio;
    char kms[8];
    char dniTitular[9];
    float precioDeAdquisicion;
} AutoArchivo;



AutoArchivo cargarAutoArchivo(Auto);


void guardarAutoArchivo(AutoArchivo, char*);
void guardarAutoArchivoEnPos(AutoArchivo, char*, int);


#endif // AUTOARCHIVO_H_INCLUDED
