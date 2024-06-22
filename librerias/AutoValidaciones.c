#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "AutoValidaciones.h"
#include "Persona.h"
#include "Utiles.h"


/**
    \brief Funcion que valida si el valor pasado como precio de adquisicion, es positivo.
    \param Float que representa el precio de adquisicion.
    \return 0 si es negativo
            1 si es positivo

**/

int PrecioNoNegativo(float valor)
{

    int retorno;

    if (valor < 0){

        retorno = 0;
    }
    else{

        retorno = 1;
    }

    return retorno;

}


/**

    \brief Funcion que valida si el titular de un auto es vendedor.
    \param Persona titular -> estructura tipo persona que representa el titular del vehiculo
    \return int -> 1 si es Vendedor
               0 si no lo es.

**/

int esVendedor(Persona titular){

    int flag = 0;
    if (titular.rol == 'V'){
        flag = 1;

    } else {
        printf("\nLa persona no tiene el rol de Vendedor");
    }

    return flag;
}
/**

    \brief Funcion que verifica que la marca igresada no sobrepase los limites del arreglo
    \param char marca[] -> el string a validar.
    \return int -> 1 si esta dentro de los limites
               0 si no.
**/

int limiteMarca(char marca[]){
    int flag = 1;

    if( strlen(marca) >= 14 ){
        flag = 0;
      printf("Error, palabra fuera de los limites");
    }
return flag;
}

/**

    \brief Funcion que verifica que el modelo igresado no sobrepase los limites del arreglo
    \param char modelo[] -> el string a validar.
    \return int -> 1 si esta dentro de los limites
               0 si no.
**/

int limiteModelo(char modelo[]){
    int flag = 0;
    if (strlen(modelo) < 20){
        flag = 1;
    }else {
        printf("Error. Palabra fuera de los limites");

    }
    return flag;
}

/**

    \brief Funcion que verifica que el año igresado este correcto.
    \param int anio -> representa el año
    \return int -> 1 si es correcto
                   0 si no.
**/

int esAnio(int anio){
    int flag = 0;
    int digitos = contarDigitos(anio);
    int noNegativo = anioNoNegativo(anio);
    int rango = limiteAnio(anio);

        if (digitos == 4 && noNegativo == 1 && rango == 1) {
           flag = 1;
        }
return flag;
}

/**

    \brief Funcion que verifica que el año igresado no sea negativo.
    \param int anio -> el año a evaluar
    \return int -> 1 si es mayor a 0
                   0 si no.
**/

int anioNoNegativo(int anio){
    int flag = 0;
    if (anio > 0){
        flag = 1;

    } else {

        printf("el a%co no puede ser negativo.\n", 164);

    }

return flag;
}

/**

    \brief Funcion que verifica que el año este dentro de unos parametros establecidos
    \param int anio -> el año a evaluar
    \return int -> 1 si es mayor a 0
                   0 si no.
**/

int limiteAnio(int anio){

    int flag = 0;
    if (anio <= 2024 && anio > 1930) {
        flag = 1;

    } else{
        printf("A%co incorrecto. el rango de posibilidades va desde 1930 a 2024\n", 164);
    }
return flag;


}



/**
    \brief Funcion que verifica que el kilometraje no se pase del limite

    \param char kms[] -> un arreglo que representa los kilometros
    \return int -> 1 si es mayor a 0
                   0 si es menor.
**/

int limiteKms(char kms[]){
    int flag = 0;

    int largo = strlen(kms);

    if(largo <= 8){
        flag = 1;
    }else{
        printf("kilomtreaje demasiado largo\n");

    }
    return flag;
    }

/**
    \brief Funcion que verifica que el kilometraje sea numerico

    \param char kms[] -> un arreglo que representa los kilometros
    \return int -> 1 si es mayor a 0
                   0 si es menor.
**/

int kmsNumerico(char kms[]){
    int flag = 0;
    int largo = strlen(kms);

    for (int i = 0; i < largo; i++){
        char x = kms[i];
        if(isdigit(x)!=0){
            flag = 1;

        }
    }
        if(flag == 0){
            printf("Los Kms no pueden contener letras\n");
        }

return flag;
}

/**
    \brief Funcion que verifica que el kilometraje no sea negativo

    \param char kms[] -> un arreglo que representa los kilometros
    \return int -> 1 si es mayor a 0
                   0 si es menor.
**/

int kmsNoNegativo(char kms[]){
    int flag = 1;
    int indice = 0;
    char aux = kms[indice];

    if (aux == '-'){
        flag = 0;
        printf("Los Kms no pueden ser negativos\n");
    }

return flag;
}
