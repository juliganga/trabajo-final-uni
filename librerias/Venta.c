#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Venta.h"
#include "VentaValidaciones.h"
#include "Persona.h"
#include "Pila.h"


#define archivoVenta "ventas.bin"

//Variables globales fuera de libreria
    Venta*arregloVentas; // arreglo dinamico de ventas
    int cantidadVentas = -1;

/** \brief Funcion que carga las ventas del archivo (si existe) en un arreglo dinamico al inicio del programa.
 *
 * \return void
 *
 */
void cargarArregloVentasInit()
{
    cantidadVentas = -1;

    if(archivoExiste(archivoVenta) == 1)
    {
        FILE * archi = fopen(archivoVenta, "rb");
        Venta venta;
        while(fread(&venta, sizeof(venta), 1, archi)>0)
        {
            cargarVentaArreglo(venta);
        }
        fclose(archi);
    }
    else
    {
        puts("El archivo ventas no existe.");
    }
}

/** \brief Funcion que muestra un menu interactivo para el usuario sobre las funciones de la libreria ventas
 *
 * \return void
 *
 */
void menuVentas()
{
    Venta venta;
    int decision = -1;

    while(decision != 0)
    {
        printf("\t-- Menu de Ventas --\n");
        printf("0 - Salir del menu\n");
        printf("1 - Registrar una venta\n");
        printf("2 - Ver todas las ventas\n");
        printf("3 - Ver solo la fecha y patente de todas las ventas\n");
        printf("4 - Buscar cuanto se recaudo en un mes de un a%co especifico\n", 164);
        printf("5 - Buscar cual venta genero la mayor ganancia\n");


    scanf("%d", &decision);

    switch(decision)
    {
        case 1:
            menuCargarVenta();
            break;
        case 2:
            for(int i = 0; i <= cantidadVentas; i++)
            {
                verVentas(arregloVentas[i]);
            }
            break;
        case 3:
            for(int i = 0; i <= cantidadVentas; i++)
            {
                verVentaFyP(arregloVentas[i]);
            }
            break;
        case 4:
            cargarAnioVenta(&venta);
            cargarMes(&venta);
            verGananciaMes(&venta);
            break;
        case 5:
            verMayor();
            break;
        }
    }
}

/** \brief Funcion que muestra solo la fecha y patente de la venta ingresada
 *
 * \return void
 *
 */
void verVentaFyP(Venta venta)
{
        printf("------------------------------------\n");
        printf("- Fecha: %i/%i/%i -\n", venta.fecha.anio, venta.fecha.mes, venta.fecha.dia);
        printf("- Patente: %s %s -\n", venta.autoAVender.letras, venta.autoAVender.numeros);
        printf("------------------------------------\n");
}

/** \brief Funcion que muestra la totalidad de la venta ingresada.
 *
 * \return void
 *
 */
void verVentas(Venta venta)
{
    printf("------------------------------------\n");
    printf("- Fecha: %i/%i/%i -\n", venta.fecha.anio, venta.fecha.mes, venta.fecha.dia);
    printf("- Patente: %s %s -\n", venta.autoAVender.letras, venta.autoAVender.numeros);
    printf("- DNI Comprador: %s -\n", venta.dniComprador);
    printf("- DNI Vendedor: %s -\n", venta.dniVendedor);
    printf("- Precio de venta: %.2f -\n", venta.precioVenta);
    printf("- Ganancias: %.2f -\n", venta.ganancia);
    printf("------------------------------------\n");
}

/** \brief Funcion que apila ganancias hasta finalizar recorriendo todas las ventas, despues de eso muestra esta venta
 *
 * \return void
 *
 */
void verMayor()
{
    Pila mayor, comp;
    inicpila(&mayor);
    inicpila(&comp);

    apilar(&mayor, arregloVentas[0].ganancia);

    for(int i = 0; i <= cantidadVentas; i++)
    {
        if(tope(&mayor) < arregloVentas[i].ganancia)
        {
            apilar(&mayor, arregloVentas[i].ganancia);
        }
    }
    for(int i = 0; i <= cantidadVentas; i++)
    {
        apilar(&comp, arregloVentas[i].ganancia);

        if(tope(&comp) == tope(&mayor))
        {
            verVentas(arregloVentas[i]);
        }
    }
}

void verGananciaMes(Venta venta)
{
    float suma;
    for(int i = 0; i <= cantidadVentas; i++)
        {
            if(venta.fecha.anio == arregloVentas[i].fecha.anio && venta.fecha.mes == arregloVentas[i].fecha.mes)
                {
                suma = suma + arregloVentas[i].ganancia;
                }
        }
}

/** \brief Funcion que llama a todas las funciones necesarias para cargar una venta
 *
 * \return void Finaliza cuando todo se haya cargado y se guarde la venta en el archivo de ventas.
 *
 */
void menuCargarVenta()
{
    Venta venta;
    system("cls");
    puts("--------- Agregando venta ---------");

    cargarAnioVenta(&venta);
    cargarMes(&venta);
    cargarDia(&venta);
    cargarDNIComprador(&venta);
    cargarDNIVendedor(&venta);
    cargarPatenteVenta(&venta);
    cargarPrecioVenta(&venta);
    cargarGanancia(&venta);

    verVentas(venta);
    cargarVentaArreglo(venta);
    fflush(stdin);
    guardarVentaFile(venta);


}


/** \brief Funcion que carga el año en que se hizo la venta.
 *
 * \param venta Venta representa la venta a registrar.
 * \return void
 *
 */
void cargarAnioVenta(Venta*venta)
{
    int verificado = 0;

    while(verificado == 0)
    {
        printf("A%co de la venta?\n", 164);
        scanf("%i", &venta->fecha.anio);
        fflush(stdin);
        printf("Estoy aca %i\n",venta->fecha.anio);

        if(verificarAnioActual(*venta) == 1 && anioPositivo(*venta) == 1)
        {
            verificado = 1;
        }
        printf("\n");
    }
}

/** \brief Funcion que carga el mes en que se hizo la venta.
 *
 * \param venta Venta Representa la venta a cargar.
 * \return void
 *
 */
void cargarMes(Venta*venta)
{
    int verificado = 0;
    while(verificado == 0)
    {
        puts("Mes de la venta?");
        fflush(stdin);
        scanf("%i", &venta->fecha.mes);
        fflush(stdin);

        if(verificarMes(*venta) == 1 && mesPositivo(*venta) == 1)
        {
            verificado = 1;
        }

        printf("\n");
    }

}

/** \brief Funcion que carga el dia en que se hizo la venta.
 *
 * \param venta Venta Representa la venta a cargar.
 * \return void
 *
 */
void cargarDia(Venta*venta)
{
    int verificado = 0;
    while(verificado == 0)
    {
        puts("Dia de la venta?");
        fflush(stdin);
        scanf("%i", &venta->fecha.dia);
        fflush(stdin);

        if(verificarDia(*venta) == 1 && diaPositivo(*venta) == 1)
        {
            verificado = 1;
        }

        printf("\n");
    }

}

/** \brief Funcion que carga el DNI del comprador en una venta.
 *
 * \param venta Venta Representa la venta a registrar.
 * \return void
 *
 */
void cargarDNIComprador(Venta*venta)
{
    int verificado = 0;
    while(verificado == 0)
    {
        puts("DNI del comprador?");
        scanf("%s", &venta->dniComprador);

        if(verificarEnteros(venta->dniComprador) == 1 && verificarDNI(venta->dniComprador) == 1 && esConsecionaria(venta->dniComprador) == 0 && verSiDNINoExiste(venta->dniComprador) == 0 && esComprador(venta->dniComprador) == 1)
        {
            verificado = 1;
        }
        printf("\n");
    }
}

/** \brief Funcion que carga el DNI de la consecionaria a la hora de vender un auto.
 *
 * \param venta Venta Representa la venta a registrar.
 * \return void
 *
 */
void cargarDNIVendedor(Venta*venta)
{
    int verificado = 0;
    while(verificado == 0)
    {
        puts("DNI del vendedor? (DNI reservado para la consecionaria '00000000')");
        scanf("%s", venta->dniVendedor);

        if(verificarEnteros(venta->dniVendedor) == 1 && verificarDNI(venta->dniVendedor) == 1 && esConsecionariaVenta(venta->dniVendedor) == 1)
        {
            verificado = 1;
        }

        printf("\n");
    }
}

/** \brief Funcion que carga el precio de venta de una venta realizada y llama a su verificacion
 *
 * \param venta Venta Representa la venta a registrar.
 * \return void
 *
 */
void cargarPrecioVenta(Venta*venta)
{
    int verificado = 0;
    while(verificado == 0)
    {
        puts("Precio de la venta?");
        scanf("%f", &venta->precioVenta);

        if(precioVentaPositivo(*venta) == 1)
        {
            verificado = 1;
        }

        printf("\n");
    }
}

/** \brief Funcion que carga una ganancia y llama a la verificacion de la misma
 *
 * \param venta Venta Representa la venta a registrar.
 * \return void Finaliza cuando el numero registrado sea valido segun la verificacion
 *
 */
void cargarGanancia(Venta*venta)
{
    int verificado = 0;
    while(verificado == 0)
    {
        puts("Ganancia de la venta?");
        scanf("%f", &venta->ganancia);
        printf("Venta %f",venta->ganancia);

        if(gananciaPositiva(*venta) == 1)
        {
            verificado = 1;
        }

        printf("\n");
    }
}

/** \brief Funcion que carga la totalidad de una patente y llama a las verificaciones de la misma.
 *
 * \param venta Venta Representa la venta a ingresar.
 * \return void
 *
 */
void cargarPatenteVenta(Venta*venta)
{
    int verificado = 0;

    while(verificado == 0)
    {
        Patente patente;
        printf("Ingresaremos la patente -> \n" );

        printf("Las letras: ");
        fflush(stdin);
        letrasMayus(gets(patente.letras));
        strcpy(venta->autoAVender.letras, &patente.letras);

        printf("Los numeros: ");
        fflush(stdin);
        gets(&patente.numeros);
        strcpy(venta->autoAVender.numeros, &patente.numeros);

        if(esAutoEnVenta(patente) == 1 && validarLetras(patente.letras) == 1 && validarNumeros(patente.numeros) == 1 && validarLimite(patente) == 1)
        {
            verificado = 1;
        }
    }
}

/** \brief Hace espacio en el arreglo de ventas para cargar una en el mismo.
 *
 * \param venta Venta Recibe una venta para registrarla en el arreglo
 * \return void
 *
 */
void cargarVentaArreglo(Venta venta)
{
    allocarEspacioVenta(&arregloVentas);
    arregloVentas[cantidadVentas] = venta;
}

/** \brief Funcion que agrega un espacio a un arreglo dinamico de ventas para ingresar la venta recientemente cargada.
 *
 * \param Venta**arreglo
 * \return void
 *
 */
void allocarEspacioVenta(Venta**arreglo)
{
    cantidadVentas++;
    *arreglo = realloc(*arreglo, sizeof(Venta) * (cantidadVentas+1));
}

/** \brief Funcion que guarda el arreglo de ventas en un archivo binario
 *
 * \param venta Venta
 * \return void
 *
 */
void guardarVentaFile(Venta venta)
{
    FILE * archi = fopen(archivoVenta, "ab");

    if(archi != NULL)
    {
        puts("Guardando...");

        fwrite(&venta, sizeof(Venta), 1, archi);
    }
    fclose(archi);
}
