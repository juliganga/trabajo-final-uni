#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

#include "Utiles.h"
#include "Persona.h"

/**

    Funcion que verifica si existe el archivo
    Params: char *nombreArchivo -> un puntero al nombre del archivo para verificar si existe.
    Return: int -> devuelve : 1 si existe
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
    Funcion que crea un archivo
    Params: char *nombreArchivo -> puntero a char, que representa la cadena del nombre del archivo
    Return : none
**/


void crearArchivo(char *nombreArchivo){
    FILE *archivo = fopen(nombreArchivo, "wb");
    fclose(archivo);
}

/**
    Funcion que muestra el contenido del archivo de Personas
    params: char *nombreArchivo -> el nombre del archivo
    Return: none

**/

void verArchivoPersonas(char *nombreArchivo){
FILE *archivo = fopen(nombreArchivo, "rb");

Persona aux;

if (archivo != NULL){

        while (fread(&aux, sizeof(Persona), 1, archivo) > 0){
            printf("detalles de la persona\n");
            printf("%s\n", aux.nombre);
            printf("%s\n", aux.direccion);
            printf("%s\n", aux.dni);
            printf("%s\n", aux.telefono);
            printf("%s\n", aux.rol);
            }


}else {

printf("problemas para abrir el archivo");

}
fclose(archivo);

}

/**
    Funcion que cuenta los digitos de un numero entero
    Params: int numero -> el numero a evaluar
    Return: int -> un entero que representa la cantidad de digitos que tiene el entero recibido por parametro

**/

int contarDigitos(int numero){
    int contador = (log10(numero) + 1);
    return contador;

}

