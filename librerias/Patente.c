#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "Patente.h"
#include "PatenteValidaciones.h"

/**
    Funcion que carga una patente.
    Args: none
    Return: Devuelve una estructura tipo Patente.
**/

Patente cargarPatente(){

Patente patente;
int letrasValidas, numerosValidos, limiteValido, existe;

do {
    do {
        printf("Ingresaremos la patente -> \n" );
        printf("Las letras: ");
        fflush(stdin);
        letrasMayus(gets(patente.letras));
        letrasValidas = validarLetras(patente.letras);

    } while (letrasValidas == 0);

    do {

        printf("Los numeros: ");
        fflush(stdin);
        gets(patente.numeros);
        numerosValidos = validarNumeros(patente.numeros);
    } while (numerosValidos == 0);
    limiteValido = validarLimite(patente);
    existe = existePatente(patente);
} while(limiteValido == 0 || existe == 1);



return patente;
}

/**
    Funcion que realiza el cambio de minusculas a mayusculas de las
    letras de una patente.
    Args: Recibe una arreglo de caracteres
    Return: none

**/


void letrasMayus(char letras[]){

    int longitud = strlen(letras);
        for (int i = 0; i < longitud; i++){
            letras[i] = toupper(letras[i]);

        }
}

