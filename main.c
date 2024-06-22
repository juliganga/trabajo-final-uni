#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Librerias Propias
#include "librerias/Auto.h"
#include "librerias/Auto.h"
#include "librerias/Usuario.h"
#include "librerias/Persona.h"
#include "librerias/Utiles.h"
#include "librerias/AutoMenu.h"
#include "librerias/LoginMenu.h"

void menuPrincipal();


int main()
{


    /*if(menuLogin() == 0) // ESTO ESTA COMENTADO PARA PROBAR MAS RAPIDO, DESCOMENTAR UNA VEZ DE QUE TODO ESTE TERMINADO
    {*/
        cargarEnArregloPersonasInit();
        cargarEnArregloAutosInit();
        //cargarArregloAutosEnVentaInit();
        //cargarArregloAutosNuevosInit();
        cargarArregloVentasInit();
        menuPrincipal();
    //}

    return 0;
}

void menuPrincipal()
{
    char decision = 's';
    int seguir = 1;
    while(seguir == 1)
    {
        puts("Que desea hacer?");
        puts("Entrar a menu de personas = P");
        puts("Entrar a menu de autos = A");
        puts("Entrar a menu de ventas = V");
        puts("Cualquier cosa para salir.");
        fflush(stdin);
        scanf("%c",&decision);
        fflush(stdin);
        pasarAMayus(&decision);

        switch(decision)
        {
            case 'P':
                mostrarMenuPersonas();
                break;
            case 'A':
                autoMenu();
                break;
            case 'V':
                menuVentas();
                break;
            default:
                seguir = 0;
                break;
        }
    }
}
