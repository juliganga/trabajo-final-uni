#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "Patente.h"
#include "PatenteValidaciones.h"
#include "Auto.h"

/**

    \brief Funcion que corrobora si existe la patente en el arreglo de autos.
    \param Patente patente -> la patente a evaluar
    \return int -> 1 si la patente existe
                   0 en otro caso

**/

int existePatente(Patente patente){
    int flag = 0;
    for (int i = 0 ; i <= cantidadAutos; i++){
        if (strcmp(patente.letras, arregloAutos[i].patente.letras) == 0 && strcmp(patente.numeros, arregloAutos[i].patente.numeros) == 0){
            flag = 1;
            printf("La patente ya existe\n");
        }

    }
return flag;

}

/**

    \brief Funcion que valida las letras de la patente.
    \param char letras[] -> un arreglo que representa las letras de la patente
    \return int -> 1 si son letras
                   0 en otro caso

**/

int validarLetras(char letras[]){
    int flag = 0;
    int largo = strlen(letras);

    for(int i =0; i<largo; i++){
        char x = letras[i];
        if(isdigit(x) == 0){
            flag = 1;
        }
    }
    if (flag == 0){
        printf("Solo se permiten letras\n");

    }
    return flag;
}

/**

    \brief Funcion que valida los numeros de la patente.
    \param char letras[] -> un arreglo que representa los numeros de la patente
    \return int -> 1 si son numeros
                   0 en otro caso

**/

int validarNumeros(char numeros[]){
    int flag = 0;
    int largo = strlen(numeros);

    for (int i = 0; i < largo; i++){
        char x = numeros[i];
        if (isdigit(x)!=0){
            flag = 1;
        }
    }
    if (flag == 0){
        printf("Solo se permiten numeros\n");

    }
return flag;

}

/**

    \brief Funcion que valida que la patente tenga tres letras y tres numeros
    \param Patente patente -> la patente a evaluar.
    \return int -> 1 si son letras, 0 en otro caso

**/
int validarLimite(Patente patente) {
    int flag = 0;


    if (strlen(patente.letras)==3 && strlen(patente.numeros) == 3){
            flag = 1;

        } else {
            printf("Se debe asegurar que tanto los numeros como las letras sean solo 3\n");
        }

return flag;
}


