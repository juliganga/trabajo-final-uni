#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Usuario.h"
#include "UsuarioValidaciones.h"
#include "Utiles.h"


/** Constante con el nombre de archivo, para persistir los usuarios **/
#define ARCHIVO_USUARIOS "Usuarios.bin"

/** Implementacion de la interface Usuario **/



/**
    \brief Funcion que carga una estructura de tipo Usuario.
           Verifica que exista el archivo, si no lo crea.
           Verifica todos los campos de la estructura sean validos.
           Al finalizar la carga guarda el usuario cargado.

    \param Usuario *usuario -> un puntero a una estructura de tipo Usuario
    \return none

**/
void crearUsuario(Usuario *usuario){


    printf("\t\t\t\t..::CREACI%cN DE USUARIO::..\n\n", 162);
    printf("Crearemos un usuario para entrar en el sistema...\n");

    if (existeArchivo(ARCHIVO_USUARIOS) == 0){
        crearArchivo(ARCHIVO_USUARIOS);
    }

    printf("Ingrese su nombre de usuario: ");
    fflush(stdin);
    gets((*usuario).nombreUsuario);

    while (existeUsuario(ARCHIVO_USUARIOS, usuario->nombreUsuario) == 1){
        printf("Ese nombre de usuario esta en uso.\n");
        printf("Ingrese su nombre de usuario: ");
        fflush(stdin);
        gets((*usuario).nombreUsuario);
    }

    printf("Ingrese su contrase%ca: ", 164);
    fflush(stdin);
    gets((*usuario).contrasenia);

    while (validarContrasenia(usuario->contrasenia) == 0) {
        printf("Ingrese su contrase%ca: ", 164);
        fflush(stdin);
        gets((*usuario).contrasenia);
    }

    guardarUsuario(ARCHIVO_USUARIOS, usuario);


    }




/**
    \brief Funcion que guarda un usuario en un archivo.
    \param recive un puntero a char, y un puntero a Usuario
    \return none

**/

void guardarUsuario(char *nombreArchivo, Usuario *usuario){
    FILE *archivo = fopen(nombreArchivo, "ab");

    if (archivo != NULL) {


            printf("Guardando...\n");
            fwrite(usuario, sizeof(Usuario), 1, archivo);
            printf("OK!\n");


    }else {

    printf("Tuvimos problemas abriendo el archivo.");

    }

    fclose(archivo);
}

/**
    \brief Funcion que autentica un usuario, verifica que el usuario y la contraseña esten en el archivo.
    \param char *nombreArchivo -> un puntero al nombre del archivo de usuarios
    \param char *nombreUsuario -> un puntero a la variable que contiene el nombre de usuario
    \param char *contrasenia -> un puntero a la variable que contiene la contraseña
    \return int -> 1 si esta autenticado
                   0 si no lo esta.

**/

int autenticar(char *nombreArchivo, char *nombreUsuario, char *contrasenia){
    FILE *archivo = fopen(nombreArchivo, "rb");
    Usuario usuario;
    int autenticado = 0;

    if (archivo !=  NULL){
        while (fread(&usuario, sizeof(Usuario), 1, archivo) > 0){
            if ( strcmpi(usuario.nombreUsuario, nombreUsuario) == 0 && strcmpi (usuario.contrasenia, contrasenia) == 0){
               autenticado = 1;
            }
        }

    } else {
        printf("Tuvimos problemas para abrir el archivo.\n");
    }

    fclose(archivo);
    return autenticado;

}

