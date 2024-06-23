#ifndef VENTA_H_INCLUDED
#define VENTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "Auto.h"
#include "pila.h"
#include "Patente.h"

/**
    DEFINICION DE VARIABLES
**/
typedef struct
{
    int dia;
    int mes;
    int anio;

} Fecha;

typedef struct
{
    Fecha fecha;
    Patente autoAVender;
    float precioVenta;
    float ganancia;
    char dniComprador[9];
    char dniVendedor[9];

} Venta;

/**
    FUNCIONES
**/

// CARGAR VENTAS
void menuCargarVenta();
void cargarAnioVenta(Venta*);
void cargarMes(Venta*);
void cargarDia(Venta*);
void cargarDNIComprador(Venta*);
void cargarDNIVendedor(Venta*);
void cargarPrecioVenta(Venta*);
void cargarGanancia(Venta*);
void cargarPatenteVenta(Venta*);
void guardarVentaFile(Venta);
// FIN CARGAR VENTAS

// UTILIDADES VENTAS
void menuVentas();
void calcularGanancia(Venta*);
// FIN UTILIDADES VENTAS

// MUESTRA DE VENTAS
void verVentaFyP();
void verArrVentas();
void verGananciaMes();
void verMayor();
// FIN DE MUESTRA DE VENTAS


// CALCULO DE GANANCIAS
void verGananciaMes(Venta);
void verGananciaMatrizAnio(Venta);
int esVendedorConsecionaria(Venta);
int esLaMismaFecha(Venta,Venta);

// FIN DE CALCULO DE GANANCIAS



#endif // VENTA_H_INCLUDED
