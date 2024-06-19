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
    Funcion que carga una estructura de tipo Usuario.
    Verifica que exista el archivo, si no lo crea.
    verifica todos los campos de la estructura sean validos.
    Al finalizar la carga guarda el usuario cargado.

    Args: recive un puntero a Usuario

    Return: none
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
    Funcion que guarda un usuario en un archivo.
    Args: recive un puntero a char, y un puntero a Usuario
    Return: none

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

/*
int autPin(char *nombreArchivo, char *pin){
    FILE *archivo = fopen(nombreArchivo, "rb");
    Usuario usuario;
    int autenticado = 0;

    if (archivo !=  NULL){
        while (fread(&usuario, sizeof(Usuario), 1, archivo) > 0){
            if ( strcmpi(usuario.pin, pin) == 0){
               autenticado = 1;
            }
        }

    } else {
        printf("Tuvimos problemas para abrir el archivo.\n");
    }

    fclose(archivo);
    return autenticado;

}*/
