#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED

typedef struct
{
    int idUsuario;                 // auto incremental
    char nombre[30];
    char apellido[30];
    char userName[20];
    char password[20];
    char mail[30];
    char genero;
    int puntaje;
    int nivel;
    int preferenciasDeContenidos  ; // pensar como administrarlos
    int rol;                     // 1: es admin - 0: es comun
    int activo;                 // indica 1 o 0 si el usuario está activo
} stUsuario;

stUsuario registrarUnUsuario(int id);
void muestraUnUsuario(stUsuario a);
void muestraUnUsuarioAdmin(stUsuario a);
void cargaArchiUsuarios(char usuarios[],int id);
void cargaArchiUnUsuario(char usuarios[],int id);
int buscaUsuario(char nombreArchivo[],char nombre[]);
void mostrarArchivoUsuario (char nombreArchivo[]);

#endif // USUARIO_H_INCLUDED
