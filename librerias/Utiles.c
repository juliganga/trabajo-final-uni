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
    switch(numero)
    {/*
        case 1:
            strcpy(string,"Enero");
            break;
        case 2:
            strcpy(string,"Febrero");
            break;
        case 3:
            strcpy(string,"Marzo");
            break;
        case 4:
            strcpy(string,"Abril");
            break;
        case 5:
            strcpy(string,"Mayo");
            break;
        case 6:
            strcpy(string,"Junio");
            break;
        case 7:
            strcpy(string,"Julio");
            break;
        case 8:
            strcpy(string,"Agosto");
            break;
        case 9:
            strcpy(string,"Septiembre");
            break;
        case 10:
            strcpy(string,"Octubre");
            break;
        case 11:
            strcpy(string,"Noviembre");
            break;
        case 12:
            return "Diciembre";
            strcpy(string,"Diciembre");
            break;
        default:
            strcpy(string,"?");
            break;*/
    }
    return meses[numero-1];
}
