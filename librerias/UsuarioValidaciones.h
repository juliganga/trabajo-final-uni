#ifndef USUARIOVALIDACIONES_H_INCLUDED
#define USUARIOVALIDACIONES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "Usuario.h"

int existeUsuario(char*, char*);
int validarContrasenia(char[]);
int esPinNumerico(char[]);
int validarPin(char[]);


#endif // USUARIOVALIDACIONES_H_INCLUDED
