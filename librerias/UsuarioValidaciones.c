#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#include "Utiles.h"
#include "UsuarioValidaciones.h"
#include "Usuario.h"

/**
    Funcion que verifica la existecia de un usuario en el archivo de usuarios.
    Utiliza el nombre de usuario como parametro para la busqueda.

    Args: recive un puntero a char que representa el nombre del archivo, y un Usuario

    Return: devuelve un Int. 1 si encontro el usuario.
                             0 si no lo encontró.
**/

int existeUsuario(char *nombreArchivo, char *nombreUsuario)
{
    FILE *archivo = fopen(nombreArchivo, "rb");

    Usuario usuarioAux;
    int resultado = 0;

    if (existeArchivo(nombreArchivo) == 1)
    {
        while (fread(&usuarioAux, sizeof(Usuario), 1, archivo) > 0)
        {
            if ( strcmpi(usuarioAux.nombreUsuario, nombreUsuario) == 0)
            {
                resultado = 1;
            }
        }
    }
    else
    {
        printf("Problemas para abrir el archivo");
    }

    fclose(archivo);
    return resultado;
}

/**
    Funcion que valida la contraseña ingresada por el usuario.
    Args: un arreglo de char
    return un int = 1 si es valida.
                    0 si no lo es.
**/

int validarContrasenia(char contrasenia[]){
    int valida = 0;
        if (strlen(contrasenia) < 8){
            printf("La contrase%ca debe tener mas de 8 caracteres\n", 164);
            printf("Intentelo de nuevo\n");

        } else {
            valida = 1;
        }

return valida;
}

/**
    Funcion que chequea el arreglo de caracteres pasado como parametro sea numerico.

    Args: recive un arreglo de caracteres.

    return: devuelve un int con un valor distinto de cero si es numerico, 0 en caso
            de que no lo sea.


**/
/*
int esPinNumerico(char pin[]){

    int numerico;

    for (int i=0; i<strlen(pin); i++){
        if (isdigit(pin[i]) == 0){
            numerico = 0;
        }

    }

    return numerico;
}

/**
    Funcion que valida el pin, chequea que sea numerico, y que la longitud del mismo sea la necesaria.
    Args: recive un arrege de caracteres
    return: devuelve un int = 1 si es valido.
                              0 si no lo es.
**/
/*
int validarPin(char pin[]){
    int valido;
    int numerico = esPinNumerico(pin);

    if (numerico != 0){

        if(strlen(pin) < 4){
            printf("EL pin debe tener al menos 4 caracteres num%cricos\n", 130);
            valido = 0;
        } else if (strlen(pin) > 4){
            printf("EL pin debe tener maximo 4 caracteres num%cricos\n", 130);
            valido = 0;
        } else {
            valido = 1;
        }

    } else {
        printf("El pin debe contener solo numeros\n");
        valido = 0;
    }
return valido;

}*/

