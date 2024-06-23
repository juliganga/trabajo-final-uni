#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

#include "Utiles.h"
#include "Persona.h"

/**

    \brief Funcion que verifica si existe el archivo
    \param char *nombreArchivo -> un puntero al nombre del archivo para verificar si existe.
    \return int -> devuelve : 1 si existe
                              0 si no

**/

int existeArchivo(char nombreArchivo[]){
    FILE *archivo = fopen(nombreArchivo, "rb");
    int valor;

    if (archivo != NULL){
        valor = 1;
    } else {
        valor = 0;
    }
    fclose(archivo);
    return valor;
}

/**
    \brief Funcion que crea un archivo
    \param char *nombreArchivo -> puntero a char, que representa la cadena del nombre del archivo
    \return none
**/


void crearArchivo(char *nombreArchivo){
    FILE *archivo = fopen(nombreArchivo, "wb");
    fclose(archivo);
}

/**
    \brief Funcion que muestra el contenido del archivo de Personas
    \param char *nombreArchivo -> el nombre del archivo
    \return none

**/



/**
    \brief Funcion que cuenta los digitos de un numero entero
    \param int numero -> el numero a evaluar
    \return int -> un entero que representa la cantidad de digitos que tiene el entero recibido por parametro

**/

int contarDigitos(int numero){
    int contador = (log10(numero) + 1);
    return contador;
}

/** \brief Traduce el mes de y devuelve u
 *
 * \param numero int numero de mes
 * \return void
 *
 */
char * traducirMes(int numero)
{
    char*meses[] = {"Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Sempiembre","Octubre","Noviembre","Diciembre"};
    return meses[numero-1];
}
