#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "Auto.h"
#include "AutoValidaciones.h"
#include "AutoArchivo.h"
#include "Persona.h"
#include "Utiles.h"




/**
    Implementación de la interface Auto

 **/

 Auto *arregloAutos;
 int cantidadAutos = -1;
/*
 Auto *arregloAutosEnVenta;
 int cantidadEnVenta = -1;

 Auto *arregloAutosNuevos;
 int cantidadNuevos = -1;*/

/**
    Funcion que carga el campo Marca de la estructura.
    Args: recive un puntero a Auto
    Return: none
**/

void cargarMarca(Auto *coche){

    printf("Ingrese la marca: ");
    fflush(stdin);
    gets((*coche).marca);


}

/**
    Funcion que carga el campo Modelo de la estructura.
    Args: recive un puntero a Auto
    Return: none
**/

void cargarModelo(Auto *coche){

    printf("Ingrese el modelo: ");
    fflush(stdin);
    gets((*coche).modelo);

}

/**
    Funcion que carga el campo Anio de la estructura.
    Args: recive un puntero a Auto
    Return: none
**/

void cargarAnio(Auto *coche){

    printf("Ingrese el a%co: ", 164);
    fflush(stdin);
    scanf("%d", &coche->anio);

}
/**
    Funcion que carga el nombre del titular del vehiculo.
    Permite elegir si se quiere agregar la consecionaria, o alguna persona en especial.

    Param: Auto* coche -> puntero a una estructura tipo auto
    Return: none
 **/


void cargarTitular(Auto *coche){

    char opcion;
    char dni[9];
    Persona consecionaria = arreglopersona[0];
    Persona aux;
    int flag = 0;

    if (cantidadpersonas <= 0){

        printf("Parece que no hay personas cargadas en el sistema.\n");
        printf("Por defecto, agregaremos a la consecionaria como titular!\n");
        coche->titular = consecionaria;

    } else {

        while(flag == 0){
            printf("flag: %d", flag);
            printf("\n\tCargaremos los datos del titular\n");
            printf("\tElija una de estas opciones:\n");
            printf("R - Persona registrada\nN - Persona nueva\nC - Concesionaria\n");
            fflush(stdin);
            scanf("%c", &opcion);

            letrasMayus(&opcion);

            switch(opcion){
            case 'R':
                printf("Ingrese el DNI de la persona: ");
                fflush(stdin);
                gets(dni);
                aux = buscarSegunDNI(dni);
                    if (strcmp(aux.dni, "0") == 0){
                        printf("la persona no se encuentra en el registro.");
                        }else {
                            verPersonaFull(aux);
                            if(esVendedor(aux) == 1){
                                coche->titular = aux;
                                flag = 1;
                            }
                        }
                break;
        case 'N':
                agregarPersona();
                if (esVendedor(arreglopersona[cantidadpersonas]) == 1){
                    coche->titular = arreglopersona[cantidadpersonas];
                    flag = 1;
                }
            break;
        case 'C':
            coche->titular = consecionaria;
            flag = 1;
            break;
        }
    }
    }

}



/**
    Funcion que carga el campo Kms de la estructura.
    Args: recive un puntero a Auto
    Return: none
**/



void cargarKms(Auto *coche){

    char kms[8];
    int evaluacion;
    int limite;
    int noNegativo;


    printf("Ingrese el kilometraje: ");
    fflush(stdin);
    gets(kms);

    limite = limiteKms(kms);
    evaluacion = kmsNumerico(kms);
    noNegativo = kmsNoNegativo(kms);
    while (evaluacion == 0 || limite == 0 || noNegativo == 0){
        printf("Vuelva a Intentarlo.\n");
        printf("Ingrese el kilometraje: ");
        fflush(stdin);
        gets(kms);
        limite = limiteKms(kms);
        evaluacion = kmsNumerico(kms);


    }

    strcpy(coche->kms, kms);

}

/**
    Funcion que carga el campo PrecioDeAdquisicion de la estructura.
    Args: recive un puntero a Auto
    Return: none
**/


void cargarPrecioAd(Auto *coche){
    float precio;
    int evaluacion;

    printf("Ingrese el precio de adquisici%cn: ", 162);
    fflush(stdin);
    scanf("%f", &precio);
    evaluacion = PrecioNoNegativo(precio);

        while(evaluacion == 0){
            printf("El precio de Adquisici%cn no puede ser un numero negativo.\n", 162);
            printf("Vuelva a Intentarlo.\n");
            printf("Ingrese el precio de adquisici%cn: ", 162);
            fflush(stdin);
            scanf("%f", &precio);
            evaluacion = PrecioNoNegativo(precio);
        }

    coche->precioDeAdquisicion = precio;
}

/**
    Funcion que carga todos los campos de la estructura Auto.
    Args: none
    Return: devuelve una estrucutra de tipo Auto cargada
**/

Auto cargarAuto(){

    Auto coche;

    printf("--------- Agregando Auto ---------\n");
    coche.patente = cargarPatente();
    cargarMarca(&coche);
    cargarModelo(&coche);
    cargarAnio(&coche);
    cargarKms(&coche);
    cargarTitular(&coche);
    cargarPrecioAd(&coche);

    return coche;
}

/**
    Funcion que muestra por pantalla, los datos de una estructura tipo Auto
    Args: recibe un puntero a Auto
    Return: none
**/

void mostrarAuto(Auto coche){
    printf(":::: DETALLES DEL AUTOMOTOR ::::\n");

    printf(":: PATENTE: %s-%s::\n", coche.patente.letras, coche.patente.numeros);
    printf(":: MARCA: %s::\n", coche.marca);
    printf(":: MODELO: %s::\n", coche.modelo);
    printf(":: A%cO: %d::\n", 165, coche.anio);
    printf(":: KILOMETRAJE: %s kms::\n", coche.kms);
    printf(":: NOMBRE DEL TITULAR: %s::\n", coche.titular.nombre);
    printf(":: PRECIO DE ADQUISICION: %.2f::\n", coche.precioDeAdquisicion);

}

/**
    Funcion que reasigna espacio para el arreglo dinamico de autos.
    Params: Auto **arr -> un puntero doble de tipo Auto al arreglo.
    return: none
**/

void designarEspacioAuto(Auto **arr){
    cantidadAutos++;
    *arr = realloc(*arr, sizeof(Auto) * (cantidadAutos+1));
}

/**
    funcion que carga un auto en el arreglo dinamico de autos.
    Params: Auto coche -> el auto a agregar
    Return: none

 **/

void cargarAutoArreglo(Auto coche){

    designarEspacioAuto(&arregloAutos);
    arregloAutos[cantidadAutos] = coche;
    //mostrarAuto(arregloAutos[cantidadAutos]);
}

/**

    Funcion que carga en el arreglo de autos, todos los autos que se encuentran en el archivo.
    Params: none
    Return: none

**/

void cargarEnArregloAutosInit(){
    cantidadAutos = -1;

    if(existeArchivo(ARCHIVO_AUTOS) == 1)
    {
        FILE *archivo = fopen(ARCHIVO_AUTOS,"rb");
        AutoArchivo coche;
        Auto aux;
        while(fread(&coche,sizeof(AutoArchivo),1,archivo) > 0)
        {
            aux = convertirAuto(coche);
            cargarAutoArreglo(aux);
        }
        fclose(archivo);
    }
    else
    {
        puts("El archivo de autos no existe.");
    }

}

/**

    Funcion que lista todos los autos, mostrado solamente marca, modelo y patente.
    Params: none
    Return none

**/

void listarAutos(){

    for (int i = 0; i <= cantidadAutos; i++){
        printf("..:: Listado de Autos ::..\n");
        printf("%d - Marca: %s - Modelo: %s - Patente: %s-%s\n" ,i+1, arregloAutos[i].marca, arregloAutos[i].modelo, arregloAutos[i].patente.letras, arregloAutos[i].patente.numeros);

    }


}

/**

    Funcion que busca un auto por su patente.
    Params: Patente patente -> la patente a buscar.
            int *pos -> un puntero a la posicion del auto.
    Return: Auto -> el coche encontrado

**/
Patente ingresarPatenteParaBuscar()
{
    Patente patente;
    int letrasValidas, numerosValidos, limiteValido, existe;

    do {
        do {
            printf("Ingresaremos la patente -> \n" );
            printf("Las letras: ");
            fflush(stdin);
            letrasMayus(gets(patente.letras));
            letrasValidas = validarLetras(patente.letras);

        } while (letrasValidas == 0);

        do {

            printf("Los numeros: ");
            fflush(stdin);
            gets(patente.numeros);
            numerosValidos = validarNumeros(patente.numeros);
        } while (numerosValidos == 0);
        limiteValido = validarLimite(patente);
        existe = existePatente(patente);
    } while(limiteValido == 0 || existe == 0);

    return patente;
}


Auto buscarAutoPatente(Patente patente, int *pos){

    int i = 0;
    int flag = 0;
    Auto coche;

    while (flag == 0 && i <= cantidadAutos){
        if (strcmp(arregloAutos[i].patente.letras, patente.letras) == 0 && strcmp(arregloAutos[i].patente.numeros, patente.numeros) == 0){
            coche = arregloAutos[i];
            (*pos) = i;
            flag = 1;
        } else {
            i++;
        }



    }

return coche;

}


/**

    Funcion que permite modificar un auto.
    Params: Auto autoModificar -> el auto a modificar
    Return: Auto -> el auto modificado

**/


Auto modificarAuto(Auto autoAModificar)
{
    int opcion = -1;
    while (opcion != 0){
        printf("Que campo desea modificar?\n");
        printf("0 - Salir\n");
        printf("1 - Marca\n");
        printf("2 - Modelo\n");
        printf("3 - A%co\n", 164);
        printf("4 - Kilometraje\n");
        printf("5 - Titular\n");
        printf("6 - Precio de adquisi%cn\n", 162);
        fflush(stdin);
        scanf("%d", &opcion);

        switch(opcion){
        case 1:
            cargarMarca(&autoAModificar);
            break;
        case 2:
            cargarModelo(&autoAModificar);
            break;
        case 3:
            cargarAnio(&autoAModificar);
            break;
        case 4:
            cargarKms(&autoAModificar);
            break;
        case 5:
            cargarTitular(&autoAModificar);
            break;
        case 6:
            cargarPrecioAd(&autoAModificar);
            break;
        }


    }

    return autoAModificar;
}

/**
    Fucnion que muestra el arreglo de autos.
    Params: none
    Return: none
 **/

void mostarArrAutos(){
 for (int i = 0;i <= cantidadAutos; i++){
    mostrarAuto(arregloAutos[i]);

 }

}

/**
    Funcion que convierte una estructura tipo AutoArchivo en una estructura tipo Auto
    Params: AutoArchivo coche -> el auto a convertir
    Return: Auto -> el auto pasado como parametro convertido.
**/

Auto convertirAuto(AutoArchivo coche){
    Auto aux;

    strcpy (aux.patente.letras, coche.patente.letras);
    strcpy (aux.patente.numeros, coche.patente.numeros);
    strcpy (aux.marca, coche.marca);
    strcpy (aux.modelo, coche.modelo);
    aux.anio = coche.anio;
    strcpy (aux.kms, coche.kms);
    aux.titular = buscarTitular(coche.dniTitular);
    aux.precioDeAdquisicion = coche.precioDeAdquisicion;

    return aux;

}
/**
    Funcion que busca una persona por dni.
    Prarams: char dni[] -> que representa el dni del titular a buscar.
    Return: Persona titular -> la persona que se corresponde al dni pasado como argumento.

**/
Persona buscarTitular(char dni[]){
    Persona titular;

    int i = 0;
    int resultado;


    while(resultado != 0 && i <= cantidadpersonas){
        titular = arreglopersona[i];
        resultado = strcmp(titular.dni, dni);
        i++;
    }

return titular;
}

/**-----------------------------------------Punto 5---------------------------------------------------------------**/

/**
    Funcion que determina si un auto esta a la venta basandose en el dni del titular, ya que la consecionaria tiene un dni
    especial.

    Params: char* nombreArchivo -> Recibe un puntero a char que representa el nombre del archivo.
    return: devuelve una estructura AutoArchivo que este en venta.
**/

int enVenta(Auto coche){
    int flag = 0;

    if(strcmp(coche.titular.dni, "00000000") == 0)
    {
        flag = 1;
    }
    return flag;


}

/**
    Funcion que reasigna espacio para el arreglo dinamico de autos en venta.
    Params: Auto **arr -> un puntero doble de tipo Auto al arreglo.
    return: none
**/
/*
void designarEspacioAutoVenta(Auto **arr){
    cantidadEnVenta++;
    *arr = realloc(*arr, sizeof(Auto) * (cantidadEnVenta+1));

}*/

/**
    Funcion que carga un auto en el arreglo dinamico de autos en venta.
    Params: Auto coche -> el auto a agregar
    Return: none

 **/
/*
void cargarAutoEnVentaEnArreglo(Auto coche){

    designarEspacioAutoVenta(&arregloAutosEnVenta);
    arregloAutosEnVenta[cantidadEnVenta] = coche;
}*/

/**
    Funcion qur carga el arreglo de autos en venta a partir del arreglo de autos.
    Params: none
    Return: none

 **/
/*
void cargarArregloAutosEnVentaInit(){
    cantidadEnVenta = -1;
    int resultado = 0;
    int i = 0;
    while (i <= cantidadAutos){
        resultado = enVenta(arregloAutos[i]);
        if (resultado == 1){
            cargarAutoEnVentaEnArreglo(arregloAutos[i]);
        }
        i++;

    }

}
*/
/**
    Funcion que recorre el arreglo de autos en venta mostrando sus elementos.
    Params: none
    Return: none

**/

void mostrarAutosEnVenta(){
    for (int i = 0; i <= cantidadAutos; i++){
        if(enVenta(arregloAutos[i]) == 1)
        {
            mostrarAuto(arregloAutos[i]);
        }
    }
}
/**----------------------------------------Ordenacion de los autos menores a 10 años---------------------------------------------------**/

/** Funcion que chequea si el auto es nuevo  **/

int esNuevo(Auto coche){

    int flag = 0;
    int limite = 2014;

    if (coche.anio >= limite){
       flag = 1;
    }

    return flag;
}

int contarNuevos(Auto arreglo[])
{
    int cantidadnuevos;
    for(int i = 0;i<=cantidadAutos;i++)
    {
        if(esNuevo(arreglo[i]) == 1)
        {
            cantidadnuevos++;
        }
    }
    return cantidadnuevos;
}





void agregarAutosNuevos(Auto**arreglo)
{
    int pos = 0;
    int nuevos = -1;
    for(int i = 0;i<=cantidadAutos;i++)
    {
        if(esNuevo(arregloAutos[i]) == 1)
        {
            nuevos++;
            insertarAutoNuevoEnArr(arregloAutos[i],nuevos,arreglo);
        }
    }
}

void insertarAutoNuevoEnArr(Auto coche,int nuevos,Auto**arreglo)
{
    *arreglo = realloc(*arreglo,sizeof(Auto)*(nuevos+1));
    (*arreglo)[nuevos] = coche;
}


int encontrarMenor(Auto arr[], int pos, int validos){
    int posMenor = pos;
    Auto aux = arr[pos];
    int i = posMenor + 1;

    while (i < validos){

        if (arr[i].anio < aux.anio){

            aux = arr[i];
            posMenor = i;
        }
        i++;
    }

return posMenor;

}

void ordenarAutos(Auto arr[], int validos){
    int i = 0;
    int posMenor;
    Auto aux;

    while(i < validos){
        posMenor = encontrarMenor(arr, i, validos);
        aux = arr[posMenor];
        arr[posMenor] = arr[i];
        arr[i] = aux;
        i++;
    }
}
/*
void designarEspacioAutoNuevos(Auto **arr){
    cantidadNuevos++;
    *arr = realloc(*arr, sizeof(Auto) * (cantidadNuevos+1));
}

void cargarAutoNuevoEnArreglo(Auto coche){

    designarEspacioAutoNuevos(&arregloAutosNuevos);
    arregloAutosNuevos[cantidadNuevos] = coche;

}

void cargarArregloAutosNuevosInit(){
    cantidadNuevos = -1;
    int resultado = 0;
    int i = 0;
    while (i <= cantidadAutos){
        resultado = esNuevo(arregloAutos[i]);
        if (resultado == 1){
            cargarAutoNuevoEnArreglo(arregloAutos[i]);
        }
        i++;

    }

}
*/

void mostrarAutosNuevos(Auto arreglo[],int validos){

    for (int i = 0; i < validos; i++){
        {
            mostrarAuto(arreglo[i]);
        }
    }

}
