#include "persona.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define archivopersona "personas.bin"


/// Variables globales fuera de libreria

Persona*arreglopersona; // Arreglo dinamico de las personas, se puede leer simplemente llamando su nombre, tratenlo como un arreglo.
cantidadpersonas = -1;// -1 es la posicion final de las personas, tambien define cuanto calloc'ear para el arreglo (n+1) ^


/// FUNCIONALIDAD ///

/** \brief Muestra el menu de opciones para que el usuario elija una de los dos opciones
 *
 * \return void Sale de la funcion cuando el usuario hace cualquier eleccion.
 *
 */
void menuCargaPersonas()
{
    char eleccion;
    while(eleccion != 'E' && eleccion != 'A' && eleccion != 'M')
    {
    system("cls");
    fflush(stdin);
    puts("Cargar una persona (A) o Modificar una persona (M)");
    puts("E para salir");
    scanf("%c",&eleccion);
    pasarAMayus(&eleccion);
    fflush(stdin);

        switch(eleccion)
        {
        case 'A':
            agregarPersona();
            break;
        case 'M':
            modificarPersona();
            break;
        case 'E':
            puts("Saliendo...");
            break;
        }
    }
}


// CARGA DE PERSONAS (EN MEMORIA)
/** \brief Interfaz que se usa para cargar datos a una variable persona.
 *
 * \return void Se debe completar todo antes de salir.
 *
 */
void agregarPersona()
{
    Persona persona;

    system("cls");
    puts("--------- Agregando persona ---------");
    printf("\n");
    fflush(stdin);


    cargarDNI(&persona);
    cargarNombre(&persona);
    cargarTEL(&persona);
    cargarDIR(&persona);
    cargarRol(&persona);
    fflush(stdin);


    cargarPersonaArreglo(persona);
    fflush(stdin);
    guardarPersonaAFile(persona);
}

/** \brief Funcion que recibe un puntero de la variable persona de la funcion agregarPersona(), Carga el DNI
 *
 * \param persona Persona* Representa la persona que esta siendo cargada
 * \return void
 *
 */
void cargarDNI(Persona* persona) /// TODO: POR RAZONES QUE NO ENTIENDO, SI EL STRING SE LLEGA A SOBREPASAR, LAS VERIFICACIONES NO SE HACEN, EL WHILE SE SALTA, Y SE EJECUTA LA SIGUIENTE FUNCION
{
    int verificado = 0;


    while(verificado == 0)
    {
        puts("DNI de la persona?");
        scanf("%s",persona->dni);
        fflush(stdin);

        if(verificarDNI(persona->dni) == 1 && verificarEnteros(persona->dni) == 1 && esConsecionaria(persona->dni) == 0 && verSiDNINoExiste(persona->dni) == 1)
        {
            verificado = 1;
        }

        printf("\n");
        fflush(stdin);
    }
}


/** \brief Funcion que recibe un puntero de la variable persona de la funcion agregarPersona(), Carga el Nombre
 *
 * \param persona Persona* Representa la persona que esta siendo cargada
 * \return void
 *
 */
void cargarNombre(Persona* persona)
{
    int verificar = 0;
    while(verificar == 0)
    {
        puts("Nombre completo de la persona?");
        fflush(stdin);
        gets(persona->nombre);
        fflush(stdin);

        if(verificarNombre(persona->nombre) == 1)
        {
            verificar = 1;
        }
    }
}

/** \brief Funcion que recibe un puntero de la variable persona de la funcion agregarPersona(), Carga el TEL
 *
 * \param persona Persona* Representa la persona que esta siendo cargada
 * \return void
 *
 */
void cargarTEL(Persona* persona)
{
    int verificado = 0;
    while(verificado == 0)
    {
        fflush(stdin);
        puts("Telefono de la persona?");
        scanf("%s",persona->telefono);
        printf("\n");
        fflush(stdin);

        if(verificarEnteros(persona->telefono) == 1 && verificarTel(persona->telefono) == 1)
        {
            verificado = 1;
        }
    }

}

/** \brief Funcion que recibe un puntero de la variable persona de la funcion agregarPersona(), Carga la DIR (no tiene checks)
 *
 * \param persona Persona* Representa la persona que esta siendo cargada
 * \return void
 *
 */
void cargarDIR(Persona* persona)
{
    int verificar = 0;
    while(verificar == 0)
    {
        fflush(stdin);
        puts("Direccion del cliente?");
        gets(persona->direccion);
        fflush(stdin);
        if(verificarDir(persona->direccion) == 1)
        {
            verificar = 1;
        }
    }


    printf("\n");
}

/** \brief Funcion que recibe un puntero de la variable persona de la funcion agregarPersona(), Carga el rol
 *
 * \param persona Persona* Representa la persona que esta siendo cargada
 * \return void
 *
 */
void cargarRol(Persona* persona)
{
    char rol;
    int verificar = 0;
    while(verificar == 0)
    {
        puts("Rol del cliente? (Vendedor o Comprador)");
        fflush(stdin);
        scanf("%c",&rol);
        pasarAMayus(&rol);
        printf("\n");
        verificar = verificarRol(rol);
    }
    (*persona).rol = rol;
}
// FIN DE CARGA DE PERSONAS.

// VERIFICACIONES
/** \brief Verifica si una string tiene solo numeros o no.
 *
 * \param cadena[] char cadena
 * \return int 1 en caso de que sea verdadero, 0 si no.
 *
 */
int verificarEnteros(char cadena[])
{
    int flag = 1;
    int largo = strlen(cadena);
    for(int i = 0; i<largo; i++)
    {
        char x = cadena[i];
        if(isdigit(x)==0)
        {
            flag = 0;
        }
    }

    if(flag == 0)
    {
        puts("Error, no es un numero.");
    }

    return flag;
}

/** \brief Verifica si el largo del nombre es mayor a 3 y menor que 48. Verifica si tiene numeros o no.
 *
 * \param nombre[] char El nombre ingresado por el usuario
 * \return int 1 si es valido, sino 0.
 *
 */
int verificarNombre(char nombre[])
{
    int flag = 1;
    int largo = strlen(nombre);

    if(largo < 3 || largo > 46)
    {
        flag = 0;
    }
    else
    {
        for(int i = 0; i<largo; i++)
        {
            char x = nombre[i];
            if(isdigit(x)!=0)
            {
                flag = 0;
            }
        }
    }

    if(flag == 0)
    {
        puts("Error, contiene numeros. O es muy largo o muy corto");
    }



    return flag;
}

/** \brief Verifica si la direccion es entre 3 characteres y 98
 *
 * \param dir[] char La direccion del usuario
 * \return int 1 si es valido, sino 0.
 *
 */
int verificarDir(char dir[])
{
    int flag = 1;

    if(strlen(dir) <= 3 || strlen(dir) >= 96)
    {
        flag = 0;
    }

    if(flag == 0)
    {
        puts("Error, es muy largo o muy corto");
    }

    return flag;
}

/** \brief verifica si el largo de dni es mayor o igual a 8
 *
 * \param dni[] char representa el dni del cliente.
 * \return int 1 si es mayor a 8, 0 si no
 *
 */
int verificarDNI(char dni[])
{
    int flag = 0;
    int largo = strlen(dni);

    if(largo == 8)
    {
        flag = 1;
    }
    else
    {
        puts("Error. El DNI no tiene la cantidad correcta de digitos");
    }
    return flag;
}


/** \brief Verifica si el rol ingresado es C o V
 *
 * \param rol char representa el rol del cliente
 * \return int retorna 1 si es correspondiente, 0 si no.
 *
 */
int verificarRol(char rol)
{
    int verificar = 0;
    if(rol == 'C' || rol == 'V')
    {
        verificar = 1;
    }
    else
    {
        puts("Error. Usar C o V");
    }
    return verificar;
}

/** \brief Verifica si el numero de telefono es mayor o igual a 10
 *
 * \param tel[] char representa el numero de telefono del cliente
 * \return int 1 si es valido, 0 si no.
 *
 */
int verificarTel(char tel[])
{
    int flag = 0;
    int largo = strlen(tel);
    if(largo >= 10 && largo<=12)
    {
        flag = 1;
    }
    else
    {
        puts("Error. El N de telefono no es suficientemente largo");
    }
    return flag;
}

// FIN DE VERIFICACIONES

// ACCIONES DE ARCHIVOS CON PERSONAS
/** \brief Guarda la persona a un archivo, definido de antemano
 *
 * \param persona Persona Representa el conjunto de una persona, todos sus datos
 * \return void Si el archivo falla en su creacion por algun motivo, esto no haria nada
 *
 */
void guardarPersonaAFile(Persona persona)
{
    FILE * arch = fopen(archivopersona,"ab");

    if(arch != NULL)
    {
        puts("Guardando...");
        fwrite(&persona,sizeof(Persona),1,arch);
    }
    fclose(arch);
}

/** \brief Guarda cambios de persona que se hicieron
 *
 * \param persona Persona Sobreescribe datos ya antes cargados del archivo de clientes
 * \param entrada int Representa la "entrada" que es al respecto del inicio del archivo
 * \return void si el archivo no existe, esto no hace nada
 *
 */
void guardarCambiosPersona(Persona persona,int entrada)
{
    FILE * arch = fopen(archivopersona,"r+b");


    if(arch != NULL)
    {
        fseek(arch,sizeof(Persona)*entrada,SEEK_SET);
        fwrite(&persona,sizeof(Persona),1,arch);
        fclose(arch);
    }

}

// FIN DE ACCIONES DE GUARDADO PERSONAS EN ARCHIVO


// MODIFICACION DE PERSONA

/** \brief Un menu en donde se escribe un dni, una vez encontrado el cliente, se le dara acceso a el menu de edicion
 *
 * \return void retorna en caso de que el archivo de clientes no exista
 *
 */
void modificarPersona()
{
    if(!archivoExiste(archivopersona))
    {
        puts("No existe el archivo de persona. Crear una persona.");
        system("pause");
        return;
    }

    system("cls");
    fflush(stdin);
    char dnibusqueda[9];
    int verificado = 0;
    mostrarPersonasMin();
    while(verificado == 0)
    {
        puts("Que persona quiere modificar (Busqueda segun DNI)");
        puts("typear E para salir");
        scanf("%s",&dnibusqueda);
        pasarAMayus(&dnibusqueda);
        fflush(stdin);

        if(strcmp(dnibusqueda,"E")==0)
        {
            return;
        }


        if(verificarDNI(dnibusqueda) == 1 && verificarEnteros(dnibusqueda) == 1 && esConsecionaria(dnibusqueda) == 0 && verSiDNINoExiste(dnibusqueda) == 0)
        {
            verificado = 1;
        }
    }

    if(verificado == 1)
    {
        Persona persona;
        int entrada = -1;
        persona = buscarSegunDNI(dnibusqueda);
        entrada = devolverNumEntrada(dnibusqueda);
        verPersonaFull(persona);
        system("pause");

        if(strcmp(persona.dni,"0")== 0 && entrada != -1)
        {
            puts("No hay nadie con ese DNI.");
        }
        else
        {
            menuDeModificacionPersona(persona,entrada);
        }
    }
}

/** \brief El menu de modificacion de entrada de cliente, tiene un rango de funciones distintas
 *
 * \param personanueva Persona Una copia que se le cambiaran los detalles del cliente antes de cargarlo
 * \param entrada int // Posicion en el archivo de cliente en el que esta el cliente
 * \return void Tiene 3 metodos de salida, uno de guardado y 2 de salida
 *
 */
void menuDeModificacionPersona(Persona personanueva,int entrada)
{
    char eleccion;
    while(eleccion != 'B' && eleccion != 'E' && eleccion != 'L')
    {
        Persona personavieja = personanueva; // para luego buscar la entrada que tienen estos datos
        system("cls");
        printf("Entrada N%i\n",entrada);
        puts("Cliente:");
        verPersonaFull(personanueva);

        printf("\n");
        puts("Que desea modificar?");
        puts("1- DNI");
        puts("2- NOMBRE");
        puts("3- TELEFONO");
        puts("4- Direccion");
        puts("5- ROL");
        printf("\n");
        puts("ACCIONES: ");
        puts("B- VOLVER");
        puts("E- SALIR");
        puts("L- Guardar");



        scanf("%c",&eleccion);
        pasarAMayus(&eleccion);
        fflush(stdin);

        switch(eleccion)
        {
        case '1':
            cargarDNI(&personanueva);
            system("pause");
            break;
        case '2':
            cargarNombre(&personanueva);
            system("pause");
            break;
        case '3':
            cargarTEL(&personanueva);
            system("pause");
            break;
        case '4':
            cargarDIR(&personanueva);
            system("pause");
            break;
        case '5':
            cargarRol(&personanueva);
            system("pause");
            break;
        case 'B':
            personanueva = personavieja;
            modificarPersona();
            break;
        case 'E':
            personanueva = personavieja;
            puts("Saliendo...");
            break;
        case 'L':
            puts("GUARDANDO...");

            if(entrada != -1)
            {
                arreglopersona[entrada] = personanueva;
                guardarCambiosPersona(personanueva,entrada-1);
            }
            else
            {
                puts("Hubo algun error.");
            }
            break;
        }
    }
}

// MUESTRA DE ALUMNOS

/** \brief Un menu dedicado para la seleccion para mostrar todos o un cliente solo
 *
 * \return void Retorna en caso de que el archivo de clientes no existe
 *
 */
void menuVerPersonas()
{
    if(!archivoExiste(archivopersona) == 1)
    {
        puts("No existe el archivo de persona. Crear una persona.");
        system("pause");
        return;
    }


    char eleccion;
    while(eleccion != 'T' && eleccion != 'U' && eleccion != 'E')
    {
        system("cls");
        fflush(stdin);
        puts("Mostrar una persona (U) o todas (T)");
        puts("E para salir");
        scanf("%c",&eleccion);
        pasarAMayus(&eleccion);
        fflush(stdin);

        switch(eleccion)
        {
        case 'T':
            mostrarPersonasMenu();
            break;
        case 'U':
            buscarUnaPersona();
            break;
        case 'E':
            puts("Saliendo...");
            break;
        }
    }


}

/** \brief Un menu dedicado para mostrar las opciones de mostrar personas, completo o simple
 *
 * \return void
 *
 */
void mostrarPersonasMenu()
{
    char eleccion;
    while(eleccion != 'C' && eleccion != 'M' && eleccion != 'E' && eleccion != 'T')
    {
        system("cls");
        fflush(stdin);
        puts("Mostrar completo (C), Mostrar minimo (M) o mostrar los datos en una tabla (T)");
        puts("E para salir");

        scanf("%c",&eleccion);
        pasarAMayus(&eleccion);

        switch(eleccion)
        {
        case 'C':
            mostrarPersonasFull();
            break;
        case 'M':
            mostrarPersonasMin();
            break;
        case 'T':
            mostrarPersonaOrdenadoSegun();
            break;
        case 'E':
            puts("Saliendo...");
            break;
        }
    }
}

/** \brief Loop que recorre el arreglo de clientes, para mostrar todos sus contenidos
 *
 * \return void
 *
 */
void mostrarPersonasFull()
{
    for(int i = 1;i<=cantidadpersonas;i++)
    {
        verPersonaFull(arreglopersona[i]);
    }
}

/** \brief Loop que recorre el arreglo de clientes, para mostrar los contenidos mas importantes
 *
 * \return void
 *
 */
void mostrarPersonasMin()
{
    for(int i = 1;i<=cantidadpersonas;i++)
    {
        verPersonaMin(arreglopersona[i]);
    }
}

/** \brief Se busca una persona segun su DNI, se hacen verificaciones. Luego se puede elegir si mostrar completamente o solo lo basico
 *
 * \return void
 *
 */
void buscarUnaPersona()
{
    fflush(stdin);
    int verificado = 0;
    char dnibusqueda[9];
    while(verificado == 0)
    {
        puts("Busqueda por DNI");
        puts("Salir con E");
        scanf("%s",&dnibusqueda);
        pasarAMayus(&dnibusqueda);

        fflush(stdin);

        if(strcmp(dnibusqueda,"E")==0)
        {
            return;
        }

        if(verificarDNI(dnibusqueda) && verificarEnteros(dnibusqueda)&& esConsecionaria(dnibusqueda) == 0 && !verSiDNINoExiste(dnibusqueda))
        {
            verificado = 1;
        }
    }

    int entrada = 0;
    Persona persona;
    persona = buscarSegunDNI(dnibusqueda);
    fflush(stdin);

    char eleccion;
    while(eleccion != 'C' && eleccion != 'M' && eleccion != 'E')
    {
        puts("Mostrar completo (C) o Mostrar minimo (M)?");
        puts("E para salir");
        scanf("%c",&eleccion);
        pasarAMayus(&eleccion);
        fflush(stdin);
        switch(eleccion)
        {
        case 'C':
            verPersonaFull(persona);
            break;
        case 'M':
            verPersonaMin(persona);
            break;
        case 'E':
            puts("Saliendo...");
            break;
        }
    }
}


/** \brief Muestra todos los datos del cliente
 *
 * \param persona Persona llega por copia
 * \return void
 *
 */
void verPersonaFull(Persona persona)
{
    puts("------------------");
    printf("DNI: %s\n",persona.dni);
    printf("Nombre: %s\n",persona.nombre);
    printf("TEL: %s\n",persona.telefono);
    printf("Direccion: %s\n",persona.direccion);
    traducirRolCliente(persona.rol);
    puts("------------------");
}

/** \brief Muestra algunos de los datos del cliente
 *
 * \param persona Persona llega por copia
 * \return void
 *
 */
void verPersonaMin(Persona persona)
{
    puts("------------------");
    printf("DNI: %s\n",persona.dni);
    printf("Nombre: %s\n",persona.nombre);
    printf("TEL: %s\n",persona.telefono);
    puts("------------------");
}
// FIN DE MOSTRAR PERSONAS

/// AYUDANTES ///
/** \brief pasa UN CARACTER a mayuscula
 *
 * \param char*caracter Un puntero al caracter para hacer mayuscula
 * \return void
 *
 */
void pasarAMayus(char*caracter)
{
    *caracter = toupper(*caracter);
}

/** \brief Muestra en consola el rol correspondiente del cliente (NO SE GUARDAN ESTAS TRADUCCIONES)
 *
 * \param rol char caracter que representa el rol del cliente
 * \return void
 *
 */
void traducirRolCliente(char rol)
{
    switch(rol)
    {
    case 'C':
        puts("ROL: Cliente");
        break;
    case 'V':
        puts("ROL: Vendedor");
        break;
    case 'S': // De special
        puts("ROL: Consecionaria");
        break;
    default:
        puts("ROL: [DESCONOCIDO, CAMBIAR!].");
        break;
    }
}

/** \brief Busca una persona segun su DNI
 *
 * \param dni[] char El DNI que se usa para buscar la persona
 * \return Persona devuelve la estructura de la persona
 *
 */
Persona buscarSegunDNI(char dni[]) // Usando arreglos
{
    int flag = 0;
    Persona persona;
    int i = 0;
    int resultado;

    if(esConsecionaria(dni) == 1)
    {
        strcpy(persona.dni,"0");
        puts("-CONSECIONARIA ENCONTRADA-");
    }
    else
    {
        while(flag == 0 && cantidadpersonas >= i)
        {
            persona = arreglopersona[i];
            resultado = strncmp(dni,persona.dni,strlen(dni));
            if(resultado == 0)
            {
                flag = 1;
            }
            else
            {
                strcpy(persona.dni,"0");
            }
            i++;
        }
    }
    return persona;
}

/** \brief Se busca el numero de entrada de el dni del cliente
 *
 * \param dni[] char El DNI que se usa para buscar la persona
 * \return int Retorna un valor (1,2,3) representando la posicion
 *
 */
int devolverNumEntrada(char dni[])
{
    int i = 1;
    int flag = 0;
    Persona persona;


    while(flag == 0 && cantidadpersonas >= i)
    {
        persona = arreglopersona[i];
        int resultado;
        resultado = strncmp(dni,persona.dni,strlen(dni));
        if(resultado == 0)
        {
            flag = 1;
        }
        else
        {
            i++;
        }
    }
    return i;
}


/** \brief Devuelve un valor de 1 o 0 segun si el dni esta presente en un arreglo
 *
 * \param dni[] char El dni del cliente que se va a insertar
 * \return int 1 si no existe, 0 si existe.
 *
 */
int verSiDNINoExiste(char dni[])
{
    int flag = 1;
    if(cantidadpersonas == -1 && !archivoExiste(archivopersona))
    {
        flag = 1;
    }
    else
    {
        int resultado;
        Persona persona;
        int i = 0;
        while(flag == 1 && cantidadpersonas >= i)
        {
            persona = arreglopersona[i];
            resultado = strncmp(dni,persona.dni,strlen(dni));
            if(resultado == 0)
            {
                flag = 0;
                puts("Se encontro con alguien que tiene el dni ingresado\n");
            }
            i++;
        }
    }

    return flag;
}



/** \brief Revisa si el archivo existe
 *
 * \param archivonombre[] char archivo
 * \return int 1 si existe, 0 si no
 *
 */
int archivoExiste(char archivonombre[])
{
    int flag = 0;
    FILE * arch = fopen(archivonombre,"rb");

    if(arch != NULL)
    {
        flag = 1;
    }
    else
    {
        flag = 0;
    }
    fclose(arch);
    return flag;
}




/** \brief Prepara el arreglo dinamico que esta definido globalmente. Teoricamente no deberia traer problemas si se ejecuta mas de una vez.
 *
 * \return void se DEBE llamar al principio del programa antes de cualquier otra funcion que usa el arreglo.
 *
 */
void cargarEnArregloPersonasInit()
{
    cantidadpersonas = -1;
    cargarPersonaConsesioanaria();

    if(archivoExiste(archivopersona) == 1)
    {
        FILE * arch = fopen(archivopersona,"rb");
        Persona persona;
        while(fread(&persona,sizeof(persona),1,arch)>0)
        {
            cargarPersonaArreglo(persona);
        }
        fclose(arch);
    }
    else
    {
        puts("El archivo personas no existe.");
    }
}

/** \brief Verifica si el dni ingresado es la consecionaria
 *
 * \param dni[] char el dni ingresado del usuario
 * \return int 1 si es 00000000, 0 si no
 *
 */
int esConsecionaria(char dni[])
{
    int flag = 0;
    int resultado = 1;
    resultado = strcmp(dni,"00000000");

    if(resultado == 0)
    {
        puts("-Dni consecionaria!-");
        flag = 1;
    }
    return flag;
}



/** \brief Hace espacio en el arreglo y carga una persona al arreglo.
 *
 * \param persona Persona Recive una copia de una persona para colocar en el arreglo
 * \return void Se puede llamar fuera de cargarEnArregloPersonasInit()
 *
 */
void cargarPersonaArreglo(Persona persona)
{
    allocarEspacioParaPersona(&arreglopersona);
    arreglopersona[cantidadpersonas] = persona;
}


/** \brief Hace espacio en el arreglo para una persona, incrementa cantidadpersonas por 1.
 *
 * \param Persona**arreglo puntero de arreglo dinamico de personas
 * \return void
 *
 */
void allocarEspacioParaPersona(Persona**arreglo)
{
    cantidadpersonas++;
    *arreglo = realloc(*arreglo,sizeof(Persona)*(cantidadpersonas+1));
}

/** \brief Prepara para cargar una persona la arreglo dinamico llamada consecionaria (esta es inmodificable y no se guarda en el archivo)
 *
 * \return void
 *
 */
void cargarPersonaConsesioanaria()
{
    Persona consecionaria;

    strcpy(consecionaria.dni,"00000000");
    strcpy(consecionaria.nombre,"CONCESIONARIA");
    strcpy(consecionaria.direccion,"[DIRECCION CONSEC]");
    strcpy(consecionaria.telefono,"0000000000");
    consecionaria.rol = 'S'; // S de special
    cargarPersonaArreglo(consecionaria);
}

/** \brief Una funcion que genera matrices de strings para ordenarlos segun lo que pide el usuario
 *
 * \return void
 *
 */
void mostrarPersonaOrdenadoSegun()
{
    int lineas,columnas;
    Persona**arrpersonalocal;
    lineas = cantidadpersonas;


    char matrizdni[lineas][9];
    char matriznombre[lineas][50];
    char matriztel[lineas][14];
    char matrizdireccion[lineas][100];
    char arreglorol[lineas];

    char rol;

	Persona persona;

	int posarr = 0;
    for(int i = 1;i<=cantidadpersonas;i++)
    {
        persona = arreglopersona[i];

        strcpy(matrizdni[posarr],persona.dni);
        strcpy(matriznombre[posarr],persona.nombre);
        strcpy(matriztel[posarr],persona.telefono);
        strcpy(matrizdireccion[posarr],persona.direccion);
        rol = persona.rol;
        arreglorol[posarr] = rol;
        posarr++;
    }



    int eleccion = 0;

    fflush(stdin);
    system("cls");
    puts("Basado en que ordenar");
    puts("1- DNI");
    puts("2- Nombre");
    puts("3- Telefono");
    puts("4- Direccion");
    puts("Cualquier cosa para salir");
    scanf("%i",&eleccion);

    int i = 0;
    int menor;
    for(int i = 0;i<cantidadpersonas;i++)
    {


        switch(eleccion)
        {
            case 1:
                menor = ordenarSegunParam(i,9,matrizdni);
                break;
            case 2:
                menor = ordenarSegunParam(i,50,matriznombre);
                break;
            case 3:
                menor = ordenarSegunParam(i,14,matriztel);
                break;
            case 4:
                menor = ordenarSegunParam(i,100,matrizdireccion);
                break;
            default:
                puts("Cancelando...");
                return;
                break;
        }


        char dni[9]; // temp
        char nombrepersona[50];
        char telefono[14];
        char direccion[100];
        char role;

        strcpy(dni,matrizdni[i]);
        strcpy(nombrepersona,matriznombre[i]);
        strcpy(telefono,matriztel[i]);
        strcpy(direccion,matrizdireccion[i]);
        role = arreglorol[i];


        strcpy(matrizdni[i],matrizdni[menor]);
        strcpy(matriznombre[i],matriznombre[menor]);
        strcpy(matriztel[i],matriztel[menor]);
        strcpy(matrizdireccion[i],matrizdireccion[menor]);
        arreglorol[i] = arreglorol[menor];


        strcpy(matrizdni[menor],dni);
        strcpy(matriznombre[menor],nombrepersona);
        strcpy(matriztel[menor],telefono);
        strcpy(matrizdireccion[menor],direccion);
        arreglorol[menor] = role;
    }

    int sizecolumnanombre = 50;
    int sizecolumnadir = 50;
    int sizecolumnatel = 15;
    int sizecolumnadni = 8;
    int sizecolumnarol = 3;

    system("cls");


    int contadordeCaracters = (sizecolumnarol + sizecolumnadni + sizecolumnadir +sizecolumnatel+5) + sizecolumnanombre;
    puts("Personas ordenadas segun lo pedido");
    puts("SE RECOMIENDA MAXIMIZAR LA VENTANA PARA ABRIR"); // La verdad no se si se puede expandir la ventana :(
    system("pause");
    imprimirSeparador(contadordeCaracters);
    printf("%-*s  |%-*s|%-*s|%-*s|%-*s\n", sizecolumnadni, "|DNI", sizecolumnanombre,"NOMBRE", sizecolumnatel, "TELEFONO",sizecolumnadir,"DIRECCION",sizecolumnarol,"ROL|"); // hace espacio para columnas


    imprimirSeparador(contadordeCaracters);
    int largopalabra = 0;
    char*direccioncambiada;
    for(int i = 0;i<cantidadpersonas;i++)
    {
        printf("|%-*s |",sizecolumnadni,matrizdni[i]);
        printf("%-*s|",sizecolumnanombre,matriznombre[i]);
        printf("%-*s|",sizecolumnatel,matriztel[i]);

        largopalabra = strlen(matrizdireccion[i]);
        direccioncambiada = acortarDireccion(matrizdireccion[i],largopalabra);

        printf("%-*s|",sizecolumnadir,direccioncambiada);
        printf("%-*c|\n",sizecolumnarol,arreglorol[i]);
        imprimirSeparador(contadordeCaracters);
    }
    system("pause");
}

/** \brief Devuelve la posicion de la matriz menor (selection sort)
 *
 * \param i int Iteracion actual
 * \param size int tamaño de la matriz
 * \param matriz[][size] char matriz de caracteres
 * \return int posicion menor del arreglo
 *
 */
int ordenarSegunParam(int i,int size,char matriz[][size])
{
    int menor = i;
    for(int j = i;j<cantidadpersonas;j++)
    {
        int resultado;
        resultado = strcmp(matriz[menor],matriz[j]);
        if(resultado == 1)
        {
            menor = j;
        }
    }
    return menor;
}

/** \brief Escribe '-' x cantidad de veces
 *
 * \param sizeChars int cantidad de veces que printea el '-'
 * \return void
 *
 */
void imprimirSeparador(int sizeChars)
{
    printf("|");
    int total = sizeChars;
    for(int i = 0;total>i;i++)
    {
        printf("-");
    }
    printf("|");
    printf("\n");
}

/** \brief Acorta una direccion y agregar '...' si es muy largo
 *
 * \param texto[] char El texto que llega de la matriz
 * \param largotexto int El largo de un texto que llega del loop
 * \return char* String que se genera
 *
 */
char * acortarDireccion(char texto[],int largotexto)
{
    int cortar = 0;
    int largoactual = 0;
    char * textonuevo;

    if(largotexto >= 46)
    {
        largotexto = 46;
        cortar = 1;
    }

    for(int i = 0;i<=largotexto;i++)
    {
        textonuevo = realloc(textonuevo, largoactual+1*sizeof(char));
        textonuevo[i] = texto[i];
        largoactual++;
    }

    if(cortar == 1)
    {
        textonuevo = realloc(textonuevo, largoactual*sizeof(char));
        largoactual++;
        textonuevo[46] = '.';
        textonuevo = realloc(textonuevo, largoactual*sizeof(char));
        largoactual++;
        textonuevo[47] = '.';
        textonuevo = realloc(textonuevo, largoactual*sizeof(char));
        largoactual++;
        textonuevo[48] = '.';
        textonuevo = realloc(textonuevo, largoactual*sizeof(char));
        largoactual++;
        textonuevo[49] = '\0';
        textonuevo = realloc(textonuevo, largoactual*sizeof(char));
    }
    return textonuevo;
}

void mostrarMenuPersonas()
{
    system("cls");
    int funcion = 1;
    int seguir = 1;
    while(seguir == 1)
    {
        puts("1=Cargar/modificar persona");
        puts("2=Mostrar persona");
        puts("Cualquier cosa para salir");

        scanf("%i",&funcion);
        switch(funcion)
        {
            case 1:
                menuCargaPersonas();
                break;
            case 2:
                menuVerPersonas();
                break;
            default:
                seguir = 0;
                break;
        }
        system("pause");
        system("cls");
    }
}


