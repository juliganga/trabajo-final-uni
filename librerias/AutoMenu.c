#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "Auto.h"
#include "AutoValidaciones.h"
#include "AutoMenu.h"
#include "AutoArchivo.h"
#include "Persona.h"
#include "Utiles.h"
#include "Patente.h"


/** \brief Menu de control de autos
 *
 * \return void
 *
 */
void autoMenu()
{

    fflush(stdin);
    int opcion = -1;
    Auto coche;
    Auto *pCoche = &coche;
    AutoArchivo cocheArchivo;
    AutoArchivo **EnVenta;

    Patente patente;
    int posicion = 0;
    int validosEnVenta = 0;



    while (opcion != 0)
    {
        system("cls");
        printf("\t..:: Menu Autos ::..\n");
        printf("Que desea hacer?\n");
        printf("0 - Salir\n");
        printf("1 - Agregar un auto\n");
        printf("2 - Modificar un auto\n");
        printf("3 - Listar Autos\n"); // marca modelo patente
        printf("4 - Ver Informaci%cn completa de un Auto\n", 162); // toda la info
        printf("5 - Ver Autos en venta por la consecionaria\n"); //marca modelo, patente año  mostrar bien esta info
        printf("6 - Mostrar autos por antiguedad (menos de 10 a%cos)\n", 164);


        printf("Elija una opcion: ");
        scanf("%d", &opcion);
        fflush(stdin);


        int nuevos = 0;
        switch(opcion)
        {
        case 1:
            printf("El auto cargado se guarda automaticamente en el archivo al finalizar la carga.\n");
            coche = cargarAuto();
            cocheArchivo = cargarAutoArchivo(coche);
            guardarAutoArchivo(cocheArchivo, ARCHIVO_AUTOS);
            cargarAutoArreglo(coche);
            break;
        case 2:
            if(hayAutos() == 1)
            {
                listarAutosMatriz();
                printf("Ingrese la Patente del auto que quiere modificar: \n");
                patente = ingresarPatenteParaBuscar();
                coche = buscarAutoPatente(patente, &posicion);
                mostrarAuto(coche);
                coche = modificarAuto(coche);
                arregloAutos[posicion] = coche;
                cocheArchivo = cargarAutoArchivo(coche);
                guardarAutoArchivoEnPos(cocheArchivo, ARCHIVO_AUTOS, posicion);
            }
            break;
        case 3:
            if(hayAutos() == 1)
            {
                listarAutosMatriz();
            }
            break;
        case 4:
            if(hayAutos() == 1)
            {
                printf("Ingrese la Patente del auto que quiere ver: \n");
                listarAutosMatriz();
                patente = ingresarPatenteParaBuscar();

                coche = buscarAutoPatente(patente, &posicion);
                mostrarAuto(arregloAutos[posicion]);
            }
            break;
        case 5:
            if(hayAutos() == 1)
            {
                mostrarAutosEnVenta();
            }
            break;
        case 6:
            if(hayAutos() == 1)
            {
                nuevos = contarNuevos(arregloAutos);
                Auto*autosnuevos;
                if(nuevos != 0)
                {
                    agregarAutosNuevos();
                    printf("Autos ordenados\n");
                    ordenarAutos(autosnuevos, nuevos);
                    mostrarAutosNuevos();
                }
                else
                {
                    puts("No hay autos nuevos...");
                }
                break;
            }
        }
    system("pause");
    }
}
