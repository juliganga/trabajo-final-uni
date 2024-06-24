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



/** \brief Función que carga una estructura tipo AutoArchivo.
 *
 * \param autoACargar Auto ecibe una estructura tipo Auto
 * \return AutoArchivo Auto para cargar a archivo
 *
 */
AutoArchivo cargarAutoArchivo(Auto autoACargar)
{

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


/** \brief Función que muestra por pantalla todos los campos de una estructura tipo AutoArchivo.
 *
 * \param coche AutoArchivo archivo
 * \return void
 *
 */
void mostrarAutoArchivo(AutoArchivo coche)
{

    printf("-----------------------------------------\n");
    printf("Patente: %s-%s\n", coche.patente.letras, coche.patente.numeros);
    printf("Marca : %s\n", coche.marca);
    printf("Modelo : %s\n", coche.modelo);
    printf("A%co : %d\n",164, coche.anio);
    printf("-----------------------------------------\n");
}






/** \brief Funcion que guarda los datos de un auto en formato AutoArchivo
 *
 * \param coche AutoArchivo el auto a guardar
 * \param nombreArchivo char* Puntero al nombre del archivo.
 * \return void
 *
 */
void guardarAutoArchivo(AutoArchivo coche, char *nombreArchivo)
{
    FILE *archivo = fopen(nombreArchivo, "ab");

    if (archivo !=NULL)
    {

        fwrite(&coche, sizeof(AutoArchivo), 1, archivo);

    }
    else
    {

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

/** \brief Funcion que guarda un AutoArchivo en la posicion indicada
 *
 * \param coche AutoArchivo El coche a guardar
 * \param nombreArchivo char* Puntero al archivo donde guardar
 * \param pos int Las posicion donde guardar el auto
 * \return void
 *
 */
void guardarAutoArchivoEnPos(AutoArchivo coche, char *nombreArchivo, int pos){
    FILE* archivo = fopen(nombreArchivo, "r+b");
    Auto aux;



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

