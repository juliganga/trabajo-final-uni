#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "Auto.h"
#include "AutoValidaciones.h"
#include "AutoMenu.h"
#include "AutoArchivo.h"
#include "Persona.h"
#include "Utiles.h"


void autoMenu(){

fflush(stdin);
int opcion = -1;
Auto coche;
Auto *pCoche = &coche;
AutoArchivo cocheArchivo;
AutoArchivo **EnVenta;

Patente patente;
int posicion = 0;
int validosEnVenta = 0;



while (opcion != 0){

    printf("\t..:: Menu Autos ::..\n");
    printf("Que desea hacer?\n");
    printf("0 - Salir\n");
    printf("1 - Agregar un auto\n");
    printf("2 - Modificar un auto\n");
    printf("3 - Listar Autos\n"); // marca modelo patente
    printf("4 - Ver Informaci%cn completa de un Auto\n", 162); // toda la info
    printf("5 - Ver Autos en venta\n"); //marca modelo, patente año  mostrar bien esta info
    printf("6 - Mostrar autos por antiguedad (menos de 10 a%cos)\n", 164);


    printf("Elija una opcion: ");
    scanf("%d", &opcion);


    int nuevos = 0;
    switch(opcion){
        case 1:
            printf("El auto cargado se guarda automaticamente en el archivo al finalizar la carga.\n");
            coche = cargarAuto();
            cocheArchivo = cargarAutoArchivo(coche);
            guardarAutoArchivo(cocheArchivo, ARCHIVO_AUTOS);
            cargarAutoArreglo(coche);
            break;
        case 2:
            printf("Ingrese la Patente del auto que quiere modificar: \n");

            patente = ingresarPatenteParaBuscar();
            coche = buscarAutoPatente(patente, &posicion);
            mostrarAuto(coche);
            coche = modificarAuto(coche);
            cocheArchivo = cargarAutoArchivo(coche);
            guardarAutoArchivoEnPos(cocheArchivo, ARCHIVO_AUTOS, posicion);
            /*
            cargarEnArregloAutosInit();
            cargarArregloAutosEnVentaInit();
            cargarArregloAutosNuevosInit();*/
            break;
        case 3:
            listarAutos();
            break;
        case 4:
            if(cantidadAutos != -1)
            {
                printf("Ingrese la Patente del auto que quiere ver: \n");
                patente = ingresarPatenteParaBuscar();

                coche = buscarAutoPatente(patente, &posicion);
                mostrarAuto(coche);
            }
            else
            {
                puts("No hay ningun auto...");
            }
            break;
        case 5:
            mostrarAutosEnVenta();
            break;
        case 6:
            //printf("Nuevos contados: %i",nuevos);
            nuevos = contarNuevos(arregloAutos);
            Auto*autosnuevos;
            if(nuevos != 0)
            {
                agregarAutosNuevos(&autosnuevos);
                printf("Autos ordenados\n");
                ordenarAutos(autosnuevos, nuevos);
                mostrarAutosNuevos(autosnuevos,nuevos);
            }
            else
            {
                puts("No hay autos nuevos...");
            }
            break;
        }
    }
}
