#include "usuario.h"
#include <stdio.h>
#include <stdlib.h>
#define ARCHI_USER "user.dat"
#include <conio.h>
#define ESC 27

/// CARGA DE UN USUARIO
stUsuario registrarUnUsuario(int id)
{
    stUsuario a;

    a.idUsuario=id;

    printf("Nombre.....:");
    fflush(stdin);
    scanf("%s",a.nombre);

    printf("Apellido...:");
    fflush(stdin);
    scanf("%s",a.apellido);

    printf("UserName...:");
    fflush(stdin);
    scanf("%s",a.userName);

    printf("password...:");
    fflush(stdin);
    scanf("%s",a.password);

    printf("Mail.......:");
    fflush(stdin);
    scanf("%s",a.mail);

    printf("Genero.....:");
    fflush(stdin);
    scanf("%c",&a.genero);

    a.puntaje = 0;
    a.nivel=0;

    ///cargarpreferencia();///hacer

    a.rol =  0;
    a.activo = 1;

    return a;
}

/// MUESTRA DE UN USUARIO
void muestraUnUsuario(stUsuario a)
{
    printf("\n========================================================================================================================");
    printf("\n1. nombre.......................: %s",a.nombre);
    printf("\n2. Apellido.....................: %s",a.apellido);
    printf("\n3. userName.....................: %s",a.userName);
    printf("\n4. password.....................: %s",a.password);
    printf("\n5. mail.........................: %s",a.mail);
    printf("\n6. genero.......................: %c",a.genero);
    printf("\n========================================================================================================================");
    ///mostrarcontenidosfav(a);
    printf("\n========================================================================================================================");
    printf("\n   id...........................: %d",a.idUsuario);
    printf("\n   puntaje......................: %d",a.puntaje);
    printf("\n   nivel........................: %d",a.nivel);
    printf("\n   rol..........................: %d",a.rol);
    printf("\n========================================================================================================================");


}

///MUESTRA DEL USUARIO ADMIN
void muestraUnUsuarioAdmin(stUsuario a)
{

    printf("\n        userName..: %s",a.userName);
    printf(  "        id........: %d",a.idUsuario);
    printf("\n        nivel.....: %d",a.nivel);
    printf(  "        rol.......: %d",a.rol);
    printf(  "        Activo....: %d",a.activo);
    printf("\n========================================================================================================================\n");


}

///CARGA DE ARCHIVOS DE USUARIOS
void cargaArchiUsuarios(char usuarios[],int id)
{
    char opcion;
    do
    {
        cargaArchiUnUsuario(usuarios,id);
        printf("\n ESC para salir o cualquier tecla para continuar");
        opcion= getch();
    }
    while(opcion!=ESC);

}

///CARGA DE ARCHIVO UN USUARIO
void cargaArchiUnUsuario(char usuarios[],int id)
{
    FILE* archi= fopen(usuarios, "ab");
    stUsuario usuario;
    if(archi!=NULL)
    {
        usuario= registrarUnUsuario(id);
        if(buscaUsuario(ARCHI_USER,usuario.userName)==1)
        {
            printf("El usuario ya existe, por favor ingrese otro\n--------------------\n");
            usuario=registrarUnUsuario(id);
        }
        fwrite(&usuario,sizeof(stUsuario),1, archi);
    }
    fclose(archi);

}

/// BUSCAR USUARIO
int buscaUsuario(char nombreArchivo[],char nombre[])
{
    FILE* archi =fopen(nombreArchivo,"rb");
    stUsuario A;
    int flag=0;
    if(archi)
    {

        while(flag == 0 && fread(&A, sizeof(stUsuario),1,archi)>0)
        {
            if(strcmp(A.userName, nombre)== 0)
            {
                flag=1;
            }

        }
        fclose(archi);
    }
    return flag;
}

/// MOSTRAR ARCHIVO USUARIO
void mostrarArchivoUsuario (char nombreArchivo[])
{
    FILE* archi = fopen(nombreArchivo, "rb");
    stUsuario a;
    if (archi)
    {
        while(fread(&a, sizeof(stUsuario),1,archi)>0)
        {
            muestraUnUsuario(a);
        }
        fclose(archi);
    }

}


