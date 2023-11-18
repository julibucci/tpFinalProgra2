#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "contenido.h"
#include "usuario.h"
#include "arboles.h"
#include "math.h"

void mostrarMenu()
{
    printf("------MENU DE OPCIONES---------------:\n");
    printf("1 - Cargar contenido\n");
    printf("2 - Mostrar contenido en inorden\n");
    printf("3 - Mostrar contenido en preorder\n");
    printf("4 - Mostrar contenido en postorder\n");
    printf("5 - Buscar contenido por ID\n");
    printf("6 - Eliminar contenido por ID\n");
    printf("0 - Salir\n");

}

int main()
{
    char nombreArchivo[] = "contenidos.dat";
    stContenido dato[100];
    int validos = 0;

    cargarContenidosEnArchi(nombreArchivo);//carga contenidos en el archivo
    validos = cargarContenidosDesdeArchivo(nombreArchivo,dato);
    printf("Validos: %d\n",validos);

    /*printf("Contenidos del arreglo: "); // Verifico que se cargaron los datos del archivo en el arreglo
    for (int i = 0; i < validos; i++)
    {
        printf("%d\n", dato[i].idContenido);
        printf("%s\n", dato[i].titulo);

    }
    printf("\n");
    */

    nodoArbolContenido* arbol = inicArbol();
    arbol = cargarArbolDesdeArreglo(arbol,dato,0,validos-1);

    //postorder(arbol);

    //printf("\n\n\n");

    //dibujarArbol(arbol,0);

    int idContenido;
    printf("Ingrese el id contenido a borrar:");
    scanf("%d",&idContenido);

    arbol = borrarNodoPorIdContenido(arbol,idContenido);

    int idContenido2;
    printf("Ingrese el id contenido que desea buscar:");
    scanf("%d",&idContenido);

    buscarNodoPorIdContenido(arbol,idContenido2);




    return 0;
}
