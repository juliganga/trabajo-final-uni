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
    system("cls");
    while(decision != 0)
    {
        printf("\t-- Menu de Ventas --\n");
        printf("0 - Salir del menu\n");
        printf("1 - Registrar una venta\n");
        printf("2 - Ver todas las ventas hechas por la consecionaria\n");
        printf("3 - Ver todas las ventas hechas por titulares externos\n");
        printf("4 - Ver solo la fecha y patente de todas las ventas de la consecionaria\n");
        printf("5 - Ver ventas segun patente y vendedor\n");
        printf("6 - Buscar cuanto se recaudo en un mes de un a%co especifico\n", 164);
        printf("7 - Buscar cuanto se recuado en un a%co especifico\n",164);
        printf("8 - Buscar cual venta genero la mayor ganancia\n");


    scanf("%d", &decision);
    fflush(stdin);

    switch(decision)
    {
        case 1:
            menuCargarVenta();
            break;
        case 2:
            if(hayVentas() == 1)
            {
                mostrarVentasConsecionaria();
            }
            break;
        case 3:
            if(hayVentas() == 1)
            {
                mostrarVentasOtros();
            }
            break;
        case 4:
            if(hayVentas() == 1)
            {
                mostrarVentasBasico();
            }
            break;
        case 5:
            if(hayVentas() == 1)
            {
                cargarDNIVendedor(&venta);
                listarAutosMatriz();
                escribirPatenteParaBuscar(&venta);
                mostrarUnaVenta(venta);
            }
            break;
        case 6:
            if(hayVentas() == 1)
            {
                cargarAnioVenta(&venta);
                cargarMes(&venta);
                verGananciaMes(venta);
            }
            break;
        case 7:
            if(hayVentas() == 1)
            {
                cargarAnioVenta(&venta);
                verGananciaMatrizAnio(venta);
            }
            break;
        case 8:
            if(hayVentas() == 1)
            {
                verMayor();
            }
            break;
        }
    system("pause");
    system("cls");
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
    puts("------------------------------------");
    printf("- Fecha: %i/%i/%i -\n", venta.fecha.anio, venta.fecha.mes, venta.fecha.dia);
    printf("- Patente: %s %s -\n", venta.autoAVender.letras, venta.autoAVender.numeros);
    printf("- DNI Comprador: %s -\n", venta.dniComprador);
    printf("- DNI Vendedor: %s -\n", venta.dniVendedor);
    printf("- Precio de venta: %.2f -\n", venta.precioVenta);
    printf("- Ganancias: %.2f -\n", venta.ganancia);
    puts("------------------------------------");
}

/** \brief Funcion que apila ganancias hasta finalizar recorriendo todas las ventas, despues de eso muestra esta venta
 *
 * \return void
 *
 */
void verMayor()
{
    int masgrande = 0;
    Pila mayor, comp;
    inicpila(&mayor);
    inicpila(&comp);

    int flag = 0;

    int i = 0;
    while(flag == 0 && cantidadVentas >= i)
    {
        if(esVendedorConsecionaria(arregloVentas[i]) == 1)
        {
            apilar(&mayor, arregloVentas[i].ganancia);
            flag = 1;
        }
        i++;
    }

    if(flag == 1)
    {
        for(int i = 0; i <= cantidadVentas; i++)
        {
            if(esVendedorConsecionaria(arregloVentas[i]) == 1 && tope(&mayor) < arregloVentas[i].ganancia)
            {
                apilar(&mayor, arregloVentas[i].ganancia);
                masgrande = i;
            }
        }
        printf("Mayor ganancia hecha por la consecionaria: %i\n",tope(&mayor));
        verVentas(arregloVentas[masgrande]);
    }
    else
    {
        printf("Todabia la consecionaria no hizo ninguna venta...\n");
    }
}

/** \brief Muestra las ganancias de un mes especifico de un año especifico
 *
 * \param busqueda Venta fecha para buscar resultados
 * \return void
 *
 */
void verGananciaMes(Venta busqueda)
{
    float ganancias = 0;
    float temp = 0;

    for(int i = 0;i<=cantidadVentas;i++)
    {
        if(esVendedorConsecionaria(arregloVentas[i]) == 1 && esLaMismaFecha(busqueda,arregloVentas[i]) == 1)
        {
            ganancias = (float)ganancias + arregloVentas[i].ganancia;
        }
    }

    printf("Ganancias del mes %s: %.2f\n",traducirMes(busqueda.fecha.mes),ganancias);
}

/** \brief Muestra mediante una matriz las ganancias de un año
 *
 * \param busqueda Venta pasa la fecha de una venta para calcular
 * \return void
 *
 */
void verGananciaMatrizAnio(Venta busqueda)
{
    float ganancias = 0;
    float temp = 0;
    float matrizanio[3][4];
    int filaactual = 0;
    int columnaactual = 0;

    for(int m = 1;m<=12;m++)
    {
        busqueda.fecha.mes = m;
        for(int i = 0;i<=cantidadVentas;i++)
        {
            if(esVendedorConsecionaria(arregloVentas[i]) == 1 && esLaMismaFecha(busqueda,arregloVentas[i]) == 1)
            {
                ganancias = (float)(ganancias + arregloVentas[i].ganancia);
            }
        }

        if(columnaactual == 4)
        {
            filaactual++;
            columnaactual = 0;
        }

        matrizanio[filaactual][columnaactual] = ganancias;
        ganancias = 0;
        columnaactual++;


    }



    int sizecolumnas = 12;

    printf(" - A%cO %i, ganancias hechas por la consecionaria -\n",165,busqueda.fecha.anio);

    imprimirSeparador(sizecolumnas*4+3);
    int linea = 0;
    for(int i = 0;i<3;i++)
    {
        printf("|%-*s|%-*s|%-*s|%-*s|\n", sizecolumnas, traducirMes(linea+1), sizecolumnas,traducirMes(linea+2), sizecolumnas,traducirMes(linea+3),sizecolumnas,traducirMes(linea+4));
        for(int m = 0;m<4;m++)
        {
            printf("|%-*.2f",sizecolumnas,matrizanio[i][m]);
            linea++;
        }
        printf("|\n");
        imprimirSeparador(sizecolumnas*4+3);
    }


}

/** \brief Funcion que llama a todas las funciones necesarias para cargar una venta
 *
 * \return void Finaliza cuando todo se haya cargado y se guarde la venta en el archivo de ventas.
 *
 */
void menuCargarVenta()
{
    if(hayPersonas() == 1 && hayAutos() == 1)
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

        Patente patente;
        strcpy(patente.letras,venta.autoAVender.letras);
        strcpy(patente.numeros,venta.autoAVender.numeros);

        cambiarTitularPorVenta(venta.dniComprador,venta.dniVendedor,venta.precioVenta,patente);
        cargarVentaArreglo(venta);
        fflush(stdin);
        guardarVentaFile(venta);
    }
    else
    {
        printf("No hay personas o autos registrados!\n");
    }
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
        Persona comprador;

        if(verificarEnteros(venta->dniComprador) == 1 && verificarDNI(venta->dniComprador) == 1 && verSiDNINoExiste(venta->dniComprador) == 0 && esComprador(venta->dniComprador) == 1)
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
        Persona vendedor;

        if(strcmp(venta->dniComprador,venta->dniVendedor) != 0)
        {

            if(verificarEnteros(venta->dniVendedor) == 1 && verificarDNI(venta->dniVendedor) == 1 && verSiDNINoExiste(venta->dniVendedor) == 0)
            {
                vendedor = buscarSegunDNI(venta->dniVendedor);
                if(esConsecionaria(venta->dniVendedor) || esVendedor(vendedor) == 1)
                {
                    verificado = 1;
                }
            }
            else
            {
                printf("La persona no existe");
            }
        }
        else
        {
            printf("Son la misma persona\n");
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
    Auto autoenventa;
    Patente patenteenventa;
    int pos = 0;
    strcpy(patenteenventa.letras,venta->autoAVender.letras);
    strcpy(patenteenventa.numeros,venta->autoAVender.numeros);
    autoenventa = buscarAutoPatente(patenteenventa,&pos);
    mostrarAuto(autoenventa);



    int verificado = 0;
    while(verificado == 0)
    {
        puts("Precio de la venta?");
        scanf("%f", &venta->precioVenta);

        if(precioVentaPositivo(*venta) == 1 && gananciaMenorQueVenta(venta->precioVenta,autoenventa.precioDeAdquisicion) == 1)
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
    Auto autoenventa;
    Patente patenteenventa;
    int pos = 0;
    strcpy(patenteenventa.letras,venta->autoAVender.letras);
    strcpy(patenteenventa.numeros,venta->autoAVender.numeros);
    autoenventa = buscarAutoPatente(patenteenventa,&pos);
    venta->ganancia = venta->precioVenta-autoenventa.precioDeAdquisicion;
    printf("GANANCIA : %f\n",venta->ganancia);

    system("pause");
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
    mostrarSegunTitular(venta->dniVendedor);

    while(verificado == 0)
    {
        Patente patente;
        printf("Ingresaremos la patente -> \n" );

        printf("Las letras: ");
        fflush(stdin);
        letrasMayus(gets(&venta->autoAVender.letras));
        fflush(stdin);
        strcpy(&patente.letras, &venta->autoAVender.letras);

        printf("Los numeros: ");
        fflush(stdin);
        scanf("%s",venta->autoAVender.numeros);
        fflush(stdin);
        strcpy(&patente.numeros,&venta->autoAVender.numeros);

        if(lePerteneceAutoYexiste(patente,venta->dniVendedor) == 1 && validarLetras(patente.letras) == 1 && validarNumeros(patente.numeros) == 1 && validarLimite(patente) == 1)
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

/** \brief Revisa si el vendedor de la venta es la consecionaria
 *
 * \param venta Venta venta para checkear
 * \return int 1 si es asi, 0 si no.
 *
 */
int esVendedorConsecionaria(Venta venta)
{
    int flag = 0;

    if(strcmp(venta.dniVendedor,"00000000") == 0)
    {
        flag = 1;
    }
    return flag;
}


/** \brief Revisa si es la misma fecha de busqueda con la de la venta
 *
 * \param busqueda Venta Objetivo a comparar
 * \param venta Venta Venta siendo comparada
 * \return int 1 si es asi, 0 si no.
 *
 */
int esLaMismaFecha(Venta busqueda,Venta venta)
{
    int flag = 0;
    if(busqueda.fecha.anio == venta.fecha.anio && busqueda.fecha.mes == venta.fecha.mes)
    {
        flag = 1;
    }
    return flag;
}


/** \brief Muestra todas las ventas hechas por la consecionaria
 *
 * \return void
 *
 */
void mostrarVentasConsecionaria()
{
    int cantidad = 0;
    for(int i = 0;i<=cantidadVentas;i++)
    {
        if(esVendedorConsecionaria(arregloVentas[i]) == 1)
        {
            verVentas(arregloVentas[i]);
            cantidad++;
        }
    }

    if(cantidad == 0)
    {
        printf("No hay resultados...\n");
    }

}


/** \brief Muestra todas las ventas hechas por otros titulares (externos a la consecionaria)
 *
 * \return void
 *
 */
void mostrarVentasOtros()
{
    int cantidad = 0;
    for(int i = 0;i<=cantidadVentas;i++)
    {
        if(esVendedorConsecionaria(arregloVentas[i]) == 0)
        {
            verVentas(arregloVentas[i]);
            cantidad++;
        }
    }

    if(cantidad == 0)
    {
        printf("No hay resultados... \n");
    }
}

/** \brief Muestra solo la fecha y patente de las ventas hechas por la consicionaria
 *
 * \return void
 *
 */
void mostrarVentasBasico()
{
    int cantidad = 0;
    for(int i = 0; i <= cantidadVentas; i++)
    {
        if(esVendedorConsecionaria(arregloVentas[i]) == 1)
        {
            verVentaFyP(arregloVentas[i]);
            cantidad++;
        }
    }

    if(cantidad == 0)
    {
        printf("No hay resultados...");
    }
}


/** \brief Muestra venta/s segun el vendedor y la patente
 *
 * \param Venta
 * \return void
 *
 */
void mostrarUnaVenta(Venta busqueda)
{
    int cantidad = 0;
    for(int i = 0;i<=cantidadVentas;i++)
    {
        if(esVendedorYpatenteEspecifica(busqueda,arregloVentas[i]) == 1)
        {
            verVentas(arregloVentas[i]);
            cantidad++;
        }
    }

    if(cantidad == 0)
    {
        printf("No hay resultados...\n");
    }

}

/** \brief Verifica si una patente y vendedor es la misma que la busqueda
 *
 * \param busqueda Venta Busqueda para que venta sea igual
 * \param venta Venta lo que se esta comparando
 * \return int si es lo mismo retorna 1, sino retorna 0
 *
 */
int esVendedorYpatenteEspecifica(Venta busqueda,Venta venta)
{
    int flag = 0;
    if(esPatenteEspecifica(busqueda,venta) == 1 && strcmp(busqueda.dniVendedor,venta.dniVendedor) == 0)
    {
        flag = 1;
    }
    return flag;
}

/** \brief
 *
 * \param busqueda Venta
 * \param venta Venta
 * \return int
 *
 */
int esPatenteEspecifica(Venta busqueda,Venta venta)
{
    int flag = 0;

    if(strcmp(busqueda.autoAVender.letras,venta.autoAVender.letras) == 0 && strcmp(busqueda.autoAVender.numeros,venta.autoAVender.numeros) == 0)
    {
        flag = 1;
    }
    return flag;
}



/** \brief Se escribe una patente para buscar ventas que hayan pasado con ella
 *
 * \param Venta*venta Puntero a ventas, se modifica solo el parametro de patente
 * \return void
 *
 */
void escribirPatenteParaBuscar(Venta*venta)
{
    int verificado = 0;

    while(verificado == 0)
    {
        Patente patente;
        printf("Ingresaremos la patente -> \n" );

        printf("Las letras: ");
        fflush(stdin);
        letrasMayus(gets(&venta->autoAVender.letras));
        fflush(stdin);
        strcpy(&patente.letras, &venta->autoAVender.letras);

        printf("Los numeros: ");
        fflush(stdin);
        scanf("%s",venta->autoAVender.numeros);
        fflush(stdin);
        strcpy(&patente.numeros,&venta->autoAVender.numeros);

        if(validarLetras(patente.letras) == 1 && validarNumeros(patente.numeros) == 1 && validarLimite(patente) == 1)
        {
            verificado = 1;
        }
    }
}

/** \brief Verifica si hay ventas
 *
 * \return int 1 si hay, 0 si no.
 *
 */
int hayVentas()
{
    int flag = 0;

    if(cantidadVentas != -1)
    {
        flag = 1;
    }
    else
    {
        puts("No hay ventas...");
    }
    return flag;
}
