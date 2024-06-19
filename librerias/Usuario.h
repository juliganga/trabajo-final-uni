#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED



typedef struct {

    char nombreUsuario[20];
    char contrasenia[15];
    char pin[5];

} Usuario;

void crearUsuario(Usuario*);
void guardarUsuario(char[], Usuario*);
int autenticar(char*, char*, char*);
int autPin(char*, char*);






#endif // USUARIO_H_INCLUDED
