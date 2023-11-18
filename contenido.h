#ifndef CONTENIDO_H_INCLUDED
#define CONTENIDO_H_INCLUDED


typedef struct
{
    int idContenido;           // auto incremental
    char titulo[30];
    char descripcion[300];
    char categoria[30];
    int likes;
    int puntosPorCompartir;
    int activo;                // indica 1 o 0 si el contenido está activo
} stContenido;

///PROTOTIPADO
stContenido ingresarCont(int id);
void mostrarContenido(stContenido c);
void mostrarContenidoAdmin(stContenido c);
void cargaArchiUnCont(char nombreArchivo[],int id);
void mostrarContenidosEnArchivo(char nombreArchivo[]);
int cargarContenidosDesdeArchivo(char nombreArchivo[], stContenido dato[]);
void cargarContenidosEnArchi(char nombreArchivo[]);
int contarContenidosEnArchivo(char nombreArchivo[]);
int leerContenidoDesdeArchivo(char nombreArchivo, stContenido contenido[], int maxElementos);
void insertarPorTitulo(stContenido contenido[], int numElementos, stContenido nuevoContenido);





#endif // CONTENIDO_H_INCLUDED
