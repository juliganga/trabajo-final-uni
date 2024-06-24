#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "Auto.h"
#include "AutoValidaciones.h"
#include "AutoArchivo.h"
#include "Persona.h"
#include "Utiles.h"
#include "Patente.h"





/**< Arreglos */
Auto *arregloAutos;
int cantidadAutos = -1;

Auto *arregloNuevos;
int cantidadNuevos = -1;

/**
    Funcion que carga el campo Marca de la estructura.
    Args: recive un puntero a Auto
    Return: none
**/


/** \brief Carga la marca del auto que se esta cargando
 *
 * \param coche Auto* El puntero del auto que se esta cargando
 * \return void
 *
 */
void cargarMarca(Auto *coche){

    printf("Ingrese la marca: ");
    fflush(stdin);
    gets((*coche).marca);


}



/** \brief Carga el modelo de un coche (no tiene verificaciones)
 *
 * \param coche Auto* Puntero del auto que se esta cargando
 * \return void
 *
 */
void cargarModelo(Auto *coche){

    printf("Ingrese el modelo: ");
    fflush(stdin);
    gets((*coche).modelo);

}



/** \brief El anio que se carga del auto
 *
 * \param coche Auto* Puntero del auto que se esta cargando
 * \return void
 *
 */
void cargarAnio(Auto *coche){

    int verificado = 0;

    while(verificado == 0)
    {
        printf("Ingrese el a%co: ", 164);
        scanf("%d", &coche->anio);
        fflush(stdin);
        if(esAnio(coche->anio) == 1)
        {
            verificado = 1;
        }
    }
}



/** \brief Se carga el titular de un auto, debe ser un vendedor/consecionaria
 *
 * \param coche Auto* El coche que se esta cargando
 * \return void
 *
 */
void cargarTitular(Auto *coche)
{

    char opcion;
    char dni[9];
    Persona consecionaria = arreglopersona[0];
    Persona aux;
    int flag = 0;

    if (cantidadpersonas <= 0)
    {

        printf("Parece que no hay personas cargadas en el sistema.\n");
        printf("Por defecto, agregaremos a la consecionaria como titular!\n");
        coche->titular = consecionaria;

    }
    else
    {

        while(flag == 0)
        {
            printf("\n\tCargaremos los datos del titular\n");
            printf("\tElija una de estas opciones:\n");
            printf("R - Persona registrada\nN - Persona nueva\nC - Concesionaria\n");
            fflush(stdin);
            scanf("%c", &opcion);

            letrasMayus(&opcion);

            switch(opcion)
            {
            case 'R':
                printf("Ingrese el DNI de la persona: ");
                fflush(stdin);
                gets(dni);
                aux = buscarSegunDNI(dni);
                if (strcmp(aux.dni, "0") == 0)
                {
                    printf("la persona no se encuentra en el registro.");
                }
                else
                {
                    verPersonaFull(aux);
                    if(esVendedor(aux) == 1)
                    {
                        coche->titular = aux;
                        flag = 1;
                    }
                }
                break;
            case 'N':
                agregarPersona();
                if (esVendedor(arreglopersona[cantidadpersonas]) == 1)
                {
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





/** \brief Se carga los kilometros del auto
 *
 * \param coche Auto*
 * \return void
 *
 */
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
        noNegativo = kmsNoNegativo(kms);
    }

    strcpy(coche->kms, kms);

}



/** \brief Carga el precio de adquisicion de un auto
 *
 * \param coche Auto* puntero de un auto
 * \return void
 *
 */
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


/** \brief Carga un auto al sistema
 *
 * \return Auto Retorna el auto cargado
 *
 */
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


/** \brief Funcion que muestra por pantalla, los datos de una estructura tipo Auto
 *
 * \param coche puntero a Auto
 * \return void
 *
 */
void mostrarAuto(Auto coche){
    printf(":::: DETALLES DEL AUTOMOTOR ::::\n");

    printf(":: PATENTE: %s-%s ::\n", coche.patente.letras, coche.patente.numeros);
    printf(":: MARCA: %s ::\n", coche.marca);
    printf(":: MODELO: %s ::\n", coche.modelo);
    printf(":: A%cO: %d ::\n", 165, coche.anio);
    printf(":: KILOMETRAJE: %s kms ::\n", coche.kms);
    printf(":: NOMBRE DEL TITULAR: %s ::\n", coche.titular.nombre);
    printf(":: PRECIO DE ADQUISICION: %.2f ::\n", coche.precioDeAdquisicion);

}



/** \brief Da espacio al arreglo autos
 *
 * \param arr Auto** Puntero de arreglo de autos
 * \return void
 *
 */
void designarEspacioAuto(Auto **arr){
    cantidadAutos++;
    *arr = realloc(*arr, sizeof(Auto) * (cantidadAutos+1));
}



/** \brief Da espacio y carga un auto en el arreglo
 *
 * \param coche Auto
 * \return void
 *
 */
void cargarAutoArreglo(Auto coche){

    designarEspacioAuto(&arregloAutos);
    arregloAutos[cantidadAutos] = coche;
}




/** \brief Carga en un arreglo todos los autos del archivo.
 *
 * \return void
 *
 */
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

/** \brief Lista todos los autos en el sistema
 *
 * \param
 * \param
 * \return void
 *
 */

void listarAutos(){

    for (int i = 0; i <= cantidadAutos; i++){
        printf("..:: Listado de Autos ::..\n");
        printf("%d - Marca: %s - Modelo: %s - Patente: %s-%s\n" ,i+1, arregloAutos[i].marca, arregloAutos[i].modelo, arregloAutos[i].patente.letras, arregloAutos[i].patente.numeros);

    }


}


/** \brief Lista autos mediante una matriz
 *
 * \return void
 *
 */
void listarAutosMatriz(){
    int filas = cantidadAutos;
    int colDim = 100;
    char autos[cantidadAutos][colDim];
    char string[colDim];
    strcpy(string, "");

    for (int i = 0; i <= cantidadAutos; i++){


        printf("%i",i);
        strcat(string,"-> Marca: ");
        strcat(string,arregloAutos[i].marca);
        strcat(string," - ");
        strcat(string,"Modelo: ");
        strcat(string,arregloAutos[i].modelo);
        strcat(string," - ");
        strcat(string,"Patente: ");
        strcat(string,arregloAutos[i].patente.letras);
        strcat(string,"-");
        strcat(string,arregloAutos[i].patente.numeros);

        strcpy(autos[i],string);
        printf("%s\n",autos[i]);
        strcpy(string, "");

    }
}

/**

    \brief Funcion que busca una patente
    \param none
    \return Patente -> la patente encontrada

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
/**

    \brief Funcion que busca un auto por su patente.
    \param Patente patente -> la patente a buscar.
            int *pos -> un puntero a la posicion del auto.
    \return Auto -> el coche encontrado

**/

Auto buscarAutoPatente(Patente patente, int *pos)
{

    int i = 0;
    int flag = 0;
    Auto coche;

    while (flag == 0 && i <= cantidadAutos)
    {
        if (strcmp(arregloAutos[i].patente.letras, patente.letras) == 0 && strcmp(arregloAutos[i].patente.numeros, patente.numeros) == 0)
        {
            coche = arregloAutos[i];
            (*pos) = i;
            flag = 1;
        }
        else
        {
            i++;
        }
    }

    return coche;

}


/** \brief Menu que permite modificar un auto.
 *
 * \param autoAModificar Auto Auto a modificar
 * \return Auto Auto modificado
 *
 */
Auto modificarAuto(Auto autoAModificar)
{
    int opcion = -1;


    while (opcion != 0){
        system("cls");
        mostrarAuto(autoAModificar);
        printf("\n\n\n");

        printf("Que campo desea modificar?\n");
        printf("0 - Salir\n");
        printf("1 - Marca\n");
        printf("2 - Modelo\n");
        printf("3 - A%co\n", 164);
        printf("4 - Kilometraje\n");
        printf("5 - Precio de adquisici%cn\n", 162);
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
            cargarPrecioAd(&autoAModificar);
            break;
        }

    }

    return autoAModificar;
}

/**
    \brief Funcion que muestra el arreglo de autos.
    \param none
    \return none
 **/

void mostarArrAutos(){
 for (int i = 0;i <= cantidadAutos; i++){
    mostrarAuto(arregloAutos[i]);

 }

}

/**
    \brief Funcion que convierte una estructura tipo AutoArchivo en una estructura tipo Auto
    \param AutoArchivo coche -> el auto a convertir
    \return Auto -> el auto pasado como parametro convertido.
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
    \brief Funcion que verifica si hay autos en el arreglo de autos
    \return int -> 1 si hay autos
                   0 si no los hay
**/

int hayAutos()
{
    int valor = 0;
    if(cantidadAutos != -1)
    {
        valor = 1;
    }
    else
    {
        puts("No hay autos...");
    }
    return valor;
}

/**
    \brief Funcion que busca una persona por dni.
    \param char dni[] -> que representa el dni del titular a buscar.
    \return Persona titular -> la persona que se corresponde al dni pasado como argumento.

**/
Persona buscarTitular(char dni[]){
    Persona titular;

    int i = 0;
    int resultado = 1;
    int flag = 0;
    strcpy(titular.nombre,"[PERSONA FALTANTE]");
    strcpy(titular.dni,"????????");

    while(flag == 0 && i <= cantidadpersonas){
        resultado = strcmp(arreglopersona[i].dni, dni);
        if(resultado == 0)
        {
            titular = arreglopersona[i];
            flag = 1;
        }
        i++;
    }

return titular;
}

/**-----------------------------------------Punto 5---------------------------------------------------------------**/

/**
    \brief Funcion que determina si un auto esta a la venta basandose en el dni del titular, ya que la consecionaria tiene un dni
    especial.

    \param Auto coche -> recibe una Estructura tipo Auto
    \return int -> 1 si el auto esta a la venta.
                -> 0 en otro caso.
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
    \brief Funcion que recorre el arreglo de autos mostrando los autos que estan en venta.
    \param none
    \return none

**/

void mostrarAutosEnVenta(){
    for (int i = 0; i <= cantidadAutos; i++){
        if(enVenta(arregloAutos[i]) == 1)
        {
            mostrarAuto(arregloAutos[i]);
        }
    }
}
/**----------------------------------------Ordenacion de los autos menores a 10 a�os---------------------------------------------------**/

/** \brief Funcion que evalua si el auto es nuevo (mayor a 2014);
    \param Auto coche -> el auto a evaluar
    \return int -> 1 si es nuevo.
                -> 0 si no.
**/

int esNuevo(Auto coche){

    int flag = 0;
    int limite = 2014;

    if (coche.anio >= limite){
       flag = 1;
    }

    return flag;
}

/**
    \brief Funcion que cuenta la cantidad de nuevos dentro del arreglo de autos.
    \param Auto arreglo[] -> el arreglo a recorrer
    \return int -> la cantidad de autos nuevos

**/

int contarNuevos(Auto arreglo[])
{
    int cantidadnuevos = 0;
    for(int i = 0;i<=cantidadAutos;i++)
    {
        if(esNuevo(arreglo[i]) == 1)
        {
            cantidadnuevos++;
        }
    }
    return cantidadnuevos;
}

/**
    \brief Funcion para agregar autos, al arreglo de autos nuevos.
    \param Auto **arreglo -> puntero doble al arreglo
    \return none
**/

void agregarAutosNuevos()
{
    for(int i = 0;i<=cantidadAutos;i++)
    {
        if(esNuevo(arregloAutos[i]) == 1)
        {
            cantidadNuevos++;
            insertarAutoNuevoEnArr(arregloAutos[i]);
        }
    }
}

/**
    \brief Funcion que asigna espacio en el arreglo para el auto a insertar y lo inserta en la ultima posicion
    \param Auto coche -> el auto a insertar
    \param int nuevos -> la cantidad de autos nuevos
    \param Auto **arreglo -> Puntero doble al arreglo.
    \return none.
**/

void insertarAutoNuevoEnArr(Auto coche)
{
    arregloNuevos = realloc(arregloNuevos,sizeof(Auto)*(cantidadNuevos+1));
    arregloNuevos[cantidadNuevos] = coche;
}

/**
    \brief funcion que busca el auto con menor a�o
    \param Auto arr[] -> el arreglo donde buscar
    \param int pos -> la posicion donde comenzar a buscar
    \param int validos -> la cantidad de registros validos en el arreglo
    \return int -> la posicion del menor.
**/

int encontrarMenor(Auto arr[], int pos, int validos)
{
    int posMenor = pos;
    Auto aux = arr[pos];
    int i = posMenor;

    while (i < validos)
    {
        if (arr[i].anio < aux.anio)
        {
            aux = arr[i];
            posMenor = i;
        }
        i++;
    }

    return posMenor;

}

/**
    \brief funcion que ordena el arreglo mediante Seleccion.
    \param Auto arr[] -> el arreglo a ordenar
    \param int validos -> la cantidad de registros validos del arreglo.
    \return none

**/

void ordenarAutos(){
    int i = 0;
    int posMenor;
    Auto aux;

    while(i < cantidadNuevos)
    {
        posMenor = encontrarMenor(arregloNuevos, i, cantidadNuevos);
        aux = arregloNuevos[posMenor];
        arregloNuevos[posMenor] = arregloNuevos[i];
        arregloNuevos[i] = aux;
        i++;
    }
}

/**
    \brief funcion que recorre el arreglo de autos nuevos y lo muestra.
    \param Auto arr[] -> el arreglo a recorrer
    \param int validos -> la cantidad de registros validos del arreglo.

**/

void mostrarAutosNuevos(){

    for (int i = 0; i <= cantidadNuevos; i++)
    {
        mostrarAuto(arregloNuevos[i]);
    }

}

/**
    \brief Funcion que cambia el titular de un auto
    \param char dnicomprador[] -> string con el dni del comprador
    \param char dnicomprador[] -> string con el dni del comprador
    \param Patente patente -> la patente del auto a modificar
    \return none
**/

void cambiarTitularPorVenta(char dnicomprador[],char dnivendedor[],float precionuevo,Patente patente)
{
    int pos = -1;
    Auto coche;
    AutoArchivo cocheArchivo;
    Persona nuevotitular;

    coche = buscarAutoPatente(patente,&pos);
    nuevotitular = buscarSegunDNI(dnicomprador);
    coche.titular = nuevotitular;
    coche.precioDeAdquisicion = precionuevo;

    arregloAutos[pos] = coche;
    mostrarAuto(arregloAutos[pos]);
    cocheArchivo = cargarAutoArchivo(coche);
    guardarAutoArchivoEnPos(cocheArchivo, ARCHIVO_AUTOS, pos);
}

/** \brief Muestra autos segun el titular del auto
 *
 * \param dni[] char DNI del vendedor
 * \return voidc
 *
 */
void mostrarSegunTitular(char dni[])
{
    printf("Autos de %s\n",dni);

    int filas = cantidadAutos;
    int colDim = 100;
    char autos[cantidadAutos][colDim];
    char string[colDim];
    strcpy(string, "");
    int resultados = 0;

    for (int i = 0; i <= cantidadAutos; i++){
        if(strcmp(arregloAutos[i].titular.dni,dni) == 0)
        {
            printf("%i",i);
            strcat(string,"-> Marca: ");
            strcat(string,arregloAutos[i].marca);
            strcat(string," - ");
            strcat(string,"Modelo: ");
            strcat(string,arregloAutos[i].modelo);
            strcat(string," - ");
            strcat(string,"Patente: ");
            strcat(string,arregloAutos[i].patente.letras);
            strcat(string,"-");
            strcat(string,arregloAutos[i].patente.numeros);

            strcpy(autos[i],string);
            printf("%s\n",autos[i]);
            strcpy(string, "");
            resultados++;
        }
    }

    if(resultados == 0)
    {
        printf("--!ESTE VENDEDOR NO TIENE NINGUN AUTO!--");
    }
}



