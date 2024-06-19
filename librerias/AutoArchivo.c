#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "AutoArchivo.h"
#include "Patente.h"
#include "Auto.h"
#include "Persona.h"

/**
    Implementacion de la interface AutoArchivo
**/



/**
    Función que carga una estructura tipo AutoArchivo.
    Params: Auto autoAcargar -> recibe una estructura tipo Auto
    Return: AutoArchivo
**/

AutoArchivo cargarAutoArchivo(Auto autoACargar){

AutoArchivo coche;

coche.patente = autoACargar.patente;
strcpy (coche.marca, autoACargar.marca);
strcpy (coche.modelo, autoACargar.modelo);
coche.anio = autoACargar.anio;
strcpy (coche.kms, autoACargar.kms);
strcpy (coche.dniTitular, autoACargar.titular.dni);
coche.precioDeAdquisicion = autoACargar.precioDeAdquisicion;

return coche;

}

/**
    Función que muestra por pantalla todos los campos de una estructura tipo AutoArchivo.
    Args: AutoArchivo
    Return: none

 **/

void mostrarAutoArchivo(AutoArchivo coche){

printf("-----------------------------------------\n");
printf("Patente: %s-%s\n", coche.patente.letras, coche.patente.numeros);
printf("Marca : %s\n", coche.marca);
printf("Modelo : %s\n", coche.modelo);
printf("A%co : %d\n",164, coche.anio);
printf("-----------------------------------------\n");
}





/**
    Funcion que guarda los datos de un auto en formato AutoArchivo
    param: AutoArchivo coche -> el auto a guardar,
           char* nombreArchivo -> puntero al nombre del archivo.

**/

void guardarAutoArchivo(AutoArchivo coche, char *nombreArchivo){
FILE *archivo = fopen(nombreArchivo, "ab");

if (archivo !=NULL){

    fwrite(&coche, sizeof(AutoArchivo), 1, archivo);

} else {

    printf("Tuvimos problemas abriendo el archivo");

}

fclose(archivo);

}

/**

Funcion que guarda un AutoArchivo en la posicion indicada
Params: AutoArchivo coche -> el coche a guardar
        char *nombreArchivo -> puntero al archivo donde guardar
        int pos -> las posicion donde guardar el auto

**/

void guardarAutoArchivoEnPos(AutoArchivo coche, char *nombreArchivo, int pos){
    FILE* archivo = fopen(nombreArchivo, "r+b");
    Auto aux;

    printf("%d", pos);



    if (archivo != NULL){
        fseek( archivo, sizeof(AutoArchivo)*pos, SEEK_SET);
        fwrite(&coche, sizeof(AutoArchivo), 1, archivo);
        aux = convertirAuto(coche);
        arregloAutos[pos] = aux;
    } else {

    printf("problemas abriendo el archivo");

    }

fclose(archivo);

}

/**

    Funcion que muestra el contenido del archivo.
    Params: char *nombreArchivo
    return: none

**/

void mostrarArchivoAutos(char *nombreArchivo){

FILE *archivo = fopen(nombreArchivo, "rb");

AutoArchivo coche;

if(archivo !=NULL){

        while (fread(&coche, sizeof(AutoArchivo), 1, archivo) > 0){

            mostrarAutoArchivo(coche);

        }

} else {
    printf("problemas con el archivo");

}
fclose(archivo);

}
