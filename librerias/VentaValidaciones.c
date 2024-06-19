#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Venta.h"
#include "VentaValidaciones.h"
#include "Persona.h"
#include "Auto.h"

#define archivopersona "personas.bin"

/** \brief Funcion que verifica si el año ingresado no es en el futuro.
 *
 * \param venta Venta
 * \return int 1 si es menor que el año actual, 0 si no
 *
 */
int verificarAnioActual(Venta venta)
{
    int flag = 0;


    if(venta.fecha.anio < 2025)
    {
        flag = 1;
    }
    else
    {
        printf("ERROR: Este a%co todavia no ocurrio", 164);
    }

    return flag;
}


/** \brief Verifica si el año proporcionado es positivo.
 *
 * \param venta Venta representa la venta a cargar
 * \return int 1 si es un numero positivo, 0 si no
 *
 */
int anioPositivo(Venta venta)
{
    int flag = 0;

    if(venta.fecha.anio > 0)
    {
        flag = 1;
    }
    else
    {
        printf("ERROR: el a%co ingresado no es un numero positivo", 164);
    }
    return flag;
}

/** \brief Verifica si el mes proporcionado existe.
 *
 * \param venta Venta
 * \return int 1 si es un mes posible, 0 si no
 *
 */
int verificarMes(Venta venta)
{
    int flag = 0;

    if(venta.fecha.mes <= 12)
    {
        flag = 1;
    }
    else
    {
        puts("ERROR: el mes ingresado es demasiado grande");
    }
    return flag;
}

/** \brief Funcion que verifica si el mes proporcionado es un numero positivo
 *
 * \param venta Venta
 * \return int 1 si es un numero positivo, 0 si no
 *
 */
int mesPositivo(Venta venta)
{
    int flag = 0;

    if(venta.fecha.mes > 0)
    {
        flag = 1;
    }
    else
    {
        puts("ERROR: el mes ingresado no es un numero positivo");
    }
    return flag;
}

/** \brief Funcion que verifica si el dia existe en un mes
 *
 * \param venta Venta
 * \return int 1 si es un dia posible, 0 si no
 *
 */
int verificarDia(Venta venta)
{
    int flag = 0;

    if(venta.fecha.dia <= 30)
    {
        flag = 1;
    }
    else
    {
        puts("ERROR: el dia ingresado excede el numero de dias de un mes");
    }
    return flag;
}

/** \brief Funcion que verifica si el dia proporcionado es positivo.
 *
 * \param venta Venta
 * \return int 1 si es un numero positivo, 0 si no
 *
 */
int diaPositivo(Venta venta)
{
    int flag = 0;

    if(venta.fecha.dia > 0)
    {
        flag = 1;
    }
    else
    {
        puts("ERROR: el dia ingresado no es un un numero positivo");
    }
    return flag;
}


/** \brief Funcion que verifica si la persona del DNI proporcionado es un comprador.
 *
 * \param dni[] char
 * \return int 1 si es un comprador, 0 si no
 *
 */
int esComprador(char dni[])
{
    int flag = 0;
    int resultado;
    Persona persona;
    int i = 0;

    while(flag == 0 && cantidadpersonas >= i)
        {
            persona = arreglopersona[i];
            resultado = strncmp(dni,persona.dni,strlen(dni));
            if(resultado == 0)
            {
                if(persona.rol == 'C')
                {
                    flag = 1;
                }
            }
            i++;
        }
    return flag;
}

/** \brief Funcion que verifica si se ingresa el DNI que se reserva para la consecionaria.
 *
 * \param dni[] char Representa el DNI reservado para la consecionaria
 * \return int 1 si es consecionaria, 0 si no
 *
 */
int esConsecionariaVenta(char dni[])
{
    int flag = 0;
    int resultado = 1;
    resultado = strcmp(dni,"00000000");

    if(resultado == 0)
    {
        flag = 1;
    }
    else
    {
        puts("ERROR: DNI INGRESADO DIFERENTE A DNI RESERVADO PARA LA CONSESIONARIA '00000000'");
    }
    return flag;
}

/** \brief Funcion que verifica si el auto que pertenece a la patente esta a la venta.
 *
 * \param patente Patente Representa la patente ingresada a la venta
 * \return int 1 si es un auto a la venta, 0 si no
 *
 */
int esAutoEnVenta(Patente patente)
{
    int flag = 0;
    int resultadoL;
    int resultadoN;

    for(int i = 0; i <= cantidadEnVenta; i++)
    {
        resultadoL = strcmp(patente.letras, arregloAutosEnVenta[i].patente.letras);
        resultadoN = strcmp(patente.numeros, arregloAutosEnVenta[i].patente.numeros);

        if(resultadoL == 0 && resultadoN == 0)
        {
            flag = 1;
        }
        else
        {
            puts("ERROR: la patente ingresada no se encuentra en la base de datos.");
        }
    }
    return flag;
}

/** \brief Funcion que verifica si el precio de venta ingresado es positivo.
 *
 * \param venta Venta Representa el precio de la venta a registrar
 * \return int 1 si es un numero positivo, 0 si no
 *
 */
int precioVentaPositivo(Venta venta)
{
    int flag = 0;

    if(venta.precioVenta > 0)
    {
        flag = 1;
    }
    else
    {
        puts("ERROR: el precio de venta ingresado no es un numero positivo");
    }
    return flag;
}

/** \brief Funcion que verifica si el numero ingresado para la ganancia de la venta es positivo.
 *
 * \param venta Venta Representa la ganancia ingresada en la venta a registrar
 * \return int 1 si es un numero positivo, 0 si no
 *
 */
int gananciaPositiva(Venta venta)
{
    int flag = 0;

    if(venta.ganancia > 0)
    {
        flag = 1;
    }
    else
    {
        puts("ERROR: la ganancia ingresada no es un numero positivo");
    }

    return flag;
}
