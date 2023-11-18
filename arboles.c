#include "arboles.h"
#include "contenido.h"
#include <stdio.h>
#include <stdlib.h>
#include "math.h"

/// 1) Inicializar el arbol
nodoArbolContenido* inicArbol ()
{
    return NULL;
}

///2) Crear nodo arbol --> Función para crear un nuevo nodo en el árbol
nodoArbolContenido* crearNodo(stContenido dato)
{
    nodoArbolContenido* nuevoNodo = (nodoArbolContenido*)malloc(sizeof(nodoArbolContenido));

    nuevoNodo->dato = dato;
    nuevoNodo->izq = NULL;
    nuevoNodo->der = NULL;

    return nuevoNodo;
}

///3) Insertar nodo ordenado por idContenido.
nodoArbolContenido* insertarArbol (nodoArbolContenido* arbol,nodoArbolContenido* dato)
{
    if(arbol != NULL)
    {
        if(dato->dato.idContenido > arbol->dato.idContenido)
        {
            arbol->der = insertarArbol(arbol->der,dato);
        }
        else
        {
            arbol->izq = insertarArbol(arbol->izq,dato);
        }

    }
    else
    {
        arbol = dato;
    }

    return arbol;
}


nodoArbolContenido* insertarNodoArbol(nodoArbolContenido* arbol, nodoArbolContenido* nuevo)
{
    if (arbol == NULL)
    {
        arbol = nuevo;
    }
    else
    {
        if (nuevo->dato.idContenido > arbol->dato.idContenido)
        {
            arbol->der = insertarNodoArbol(arbol->der, nuevo);
        }
        else
        {
            arbol->izq = insertarNodoArbol(arbol->izq, nuevo);
        }
    }
    return arbol;
}

/// 4) Mostrar un arbol --> PREORDER
void preorder(nodoArbolContenido * arbol)
{
    if(arbol != NULL)
    {
        printf("ID: %d\n", arbol->dato.idContenido);
        printf("Título: %s\n", arbol->dato.titulo);
        printf("Descripción: %s\n", arbol->dato.descripcion);
        printf("Categoría: %s\n", arbol->dato.categoria);
        printf("Likes: %d\n", arbol->dato.likes);
        printf("Puntos por Compartir: %d\n", arbol->dato.puntosPorCompartir);
        printf("Activo: %d\n", arbol->dato.activo);
        printf("\n");
        preorder(arbol->izq);
        preorder(arbol->der);
    }
}

/// Mostrar un arbol --> INORDER
void inorder(nodoArbolContenido* arbol)
{
    if (arbol != NULL)
    {
        inorder(arbol->izq);
        printf("ID: %d\n", arbol->dato.idContenido);
        printf("Título: %s\n", arbol->dato.titulo);
        printf("Descripción: %s\n", arbol->dato.descripcion);
        printf("Categoría: %s\n", arbol->dato.categoria);
        printf("Likes: %d\n", arbol->dato.likes);
        printf("Puntos por Compartir: %d\n", arbol->dato.puntosPorCompartir);
        printf("Activo: %d\n", arbol->dato.activo);
        printf("\n");
        inorder(arbol->der);
    }
}

/// Mostrar un arbol --> POSORDER
void postorder(nodoArbolContenido * arbol)
{
    if(arbol != NULL)
    {
        postorder(arbol->izq);
        postorder(arbol->der);
        printf("ID: %d\n", arbol->dato.idContenido);
        printf("Título: %s\n", arbol->dato.titulo);
        printf("Descripción: %s\n", arbol->dato.descripcion);
        printf("Categoría: %s\n", arbol->dato.categoria);
        printf("Likes: %d\n", arbol->dato.likes);
        printf("Puntos por Compartir: %d\n", arbol->dato.puntosPorCompartir);
        printf("Activo: %d\n", arbol->dato.activo);
        printf("\n");
    }
}

/// 5) Borrar un nodo arbol buscarlo por idContenido.
nodoArbolContenido* borrarNodoPorIdContenido(nodoArbolContenido* arbol, int idContenido)
{
    if (arbol == NULL)
    {
        return arbol; // Árbol vacío o nodo no encontrado
    }

    if (idContenido < arbol->dato.idContenido)
    {
        arbol->izq = borrarNodoPorIdContenido(arbol->izq, idContenido);
    }
    else if (idContenido > arbol->dato.idContenido)
    {
        arbol->der = borrarNodoPorIdContenido(arbol->der, idContenido);
    }
    else
    {
        // Nodo encontrado, realiza la eliminación
        if (arbol->izq == NULL)
        {
            nodoArbolContenido* temp = arbol->der;
            free(arbol);
            return temp;
        }
        else if (arbol->der == NULL)
        {
            nodoArbolContenido* temp = arbol->izq;
            free(arbol);
            return temp;
        }
        nodoArbolContenido* sucesor = arbol->der;
        while (sucesor->izq != NULL)
        {
            sucesor = sucesor->izq;
        }
        arbol->dato = sucesor->dato;
        arbol->der = borrarNodoPorIdContenido(arbol->der, sucesor->dato.idContenido);
    }
    return arbol;
}

/// 6)Buscar contenido en el arbol por idContenido
/*nodoArbolContenido* buscarNodoPorIdContenido(nodoArbolContenido* arbol, int idContenido)
{
    if(arbol != NULL)
    {
        if (idContenido < arbol->dato.idContenido)
        {
            arbol->izq = buscarNodoPorIdContenido(arbol->izq, idContenido);
        }
        else if (idContenido > arbol->dato.idContenido)
        {
            arbol->der = buscarNodoPorIdContenido(arbol->der, idContenido);
        }

        return arbol;
    }
}
*/
nodoArbolContenido* buscarNodoPorIdContenido(nodoArbolContenido* arbol, int idContenido)
{
    if (arbol == NULL)
    {
        printf("No se ha encontrado\n");

    }
    else
    {
        if (idContenido < arbol->dato.idContenido)
        {
            arbol = buscarNodoPorIdContenido(arbol->izq, idContenido);
        }
        else if (idContenido > arbol->dato.idContenido)
        {
            arbol = buscarNodoPorIdContenido(arbol->der, idContenido);
        }
        else
        {
            // Nodo encontrado, imprime sus datos
            printf("ID: %d\n", arbol->dato.idContenido);
            printf("Título: %s\n", arbol->dato.titulo);
            printf("Descripción: %s\n", arbol->dato.descripcion);
            printf("Categoría: %s\n", arbol->dato.categoria);
            printf("Likes: %d\n", arbol->dato.likes);
            printf("Puntos por Compartir: %d\n", arbol->dato.puntosPorCompartir);
            printf("Activo: %d\n", arbol->dato.activo);
            return arbol;
        }


    }


}


/// Función para insertar un elemento en el árbol de manera balanceada
nodoArbolContenido* insertarEnArbolBalanceado(nodoArbolContenido* arbol, stContenido dato)
{
    if (arbol == NULL)
    {
        nodoArbolContenido* nuevoNodo = crearNodo(dato);
    }

    if (dato.idContenido < arbol->dato.idContenido)
    {
        arbol->izq = insertarEnArbolBalanceado(arbol->izq, dato);
    }
    else
    {
        arbol->der = insertarEnArbolBalanceado(arbol->der, dato);
    }

    return arbol;
}

/// Función para cargar un árbol balanceado desde un arreglo ordenado por idContenido
// desde el main inicio = 0, fin = v-1
nodoArbolContenido* cargarArbolDesdeArreglo(nodoArbolContenido* arbol, stContenido dato[], int inicio, int fin) //fin = validos-1
{

    if(inicio<=fin)
    {

        int medio = floor((inicio + fin)/ 2);
        printf("posmedio %d",medio);

        arbol = insertarArbol(arbol,crearNodo(dato[medio]));

        arbol = cargarArbolDesdeArreglo(arbol, dato,inicio, medio - 1);
        arbol = cargarArbolDesdeArreglo(arbol, dato,  medio + 1, fin);


    }


    return arbol;

}

void dibujarArbol(nodoArbolContenido* arbol, int nivel)
{
    if (arbol)
    {
        // Imprimir el subárbol derecho
        dibujarArbol(arbol->der, nivel + 1);

        // Imprimir espacios y conectores
        for (int i = 0; i < nivel; i++)
        {
            if (i == nivel - 1)
            {
                printf("+--");
            }
            else
            {
                printf("     ");
            }
        }

        // Imprimir el valor del nodo actual
        printf("|%d|\n", arbol->dato.idContenido);

        // Imprimir el subárbol izquierdo
        dibujarArbol(arbol->izq, nivel + 1);
    }

}

