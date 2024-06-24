#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "LoginMenu.h"
#include "Usuario.h"
#include "UsuarioValidaciones.h"
#include "Utiles.h"

/** \brief Menu en donde el usuario puede logearse al sistema
 *
 * \return int Si es -1, no entrara si es 0 entrara
 *
 */
int menuLogin(){
    char *nombreArchivo = "Usuarios.bin";
    char *nombre = (char*) malloc(sizeof(char) * 20);
    char *contrasenia = (char*) malloc(sizeof(char) * 30);
    char *pin = (char*) malloc(sizeof(char) * 5);

    int opcion;
    int salida = -1;
    int existeArch = existeArchivo(nombreArchivo);
    Usuario user;

    printf("..:: Bienvenindo al sistema de gestion de Concesionaria ::..\n");

    if (existeArch == 0){
        printf("Parece que no existe el archivo de usuarios.\n ");
        printf("Creando archivo...\n ");
        crearArchivo(nombreArchivo);
        printf("Listo. Ahora puede crear un Usuario.\n");
    }

    do{
        printf("..::LOGIN::..\n");
        printf("..::OPCIONES::..\n");
        printf("0 - Salir\n");
        printf("1 - Crear un Usuario\n");
        printf("2 - Ingresar\n");
        printf("Elija una opcion: ");
        scanf("%d", &opcion);
        fflush(stdin);

        switch(opcion){
        case 1:
            crearUsuario(&user);
            printf("Listo! Usuario creado!\n");
            printf("Ahora puede ingresar al sistema.\n");
            break;
        case 2:
            printf("ingrese nombre: ");
            fflush(stdin);
            gets(nombre);
            printf("ingrese la contrase%ca: ", 164);
            fflush(stdin);
            gets(contrasenia);

            if (autenticar(nombreArchivo, nombre, contrasenia) == 1){
                printf("Usuario autenticado\n");
                opcion = 0;
                salida = 0;
            } else {
                printf("problemas para autenticar el usuario!\n");
            }
            break;
        default:
            salida = -1; // Salida forzada...
            break;

        }


    } while (opcion !=0);

    return salida;
}






