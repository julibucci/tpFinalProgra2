#ifndef ARBOLES_H_INCLUDED
#define ARBOLES_H_INCLUDED
#include "contenido.h"
#include "math.h"

typedef struct
{
    stContenido dato;
    struct nodoArbolContenido * izq;
    struct nodoArbolContenido * der;
} nodoArbolContenido ;

/// PROTOTIPADO
nodoArbolContenido* inicArbol ();
nodoArbolContenido* crearNodo(stContenido dato);
nodoArbolContenido* insertarNodoArbol(nodoArbolContenido* arbol, nodoArbolContenido* nuevo);
void preorder(nodoArbolContenido * arbol);
void inorder(nodoArbolContenido* arbol);
void postorder(nodoArbolContenido * arbol);
nodoArbolContenido* borrarNodoPorIdContenido(nodoArbolContenido* arbol, int idContenido);
nodoArbolContenido* buscarNodoPorIdContenido(nodoArbolContenido* arbol, int idContenido);
nodoArbolContenido* insertarEnArbolBalanceado(nodoArbolContenido* arbol, stContenido dato);
nodoArbolContenido* cargarArbolDesdeArreglo(nodoArbolContenido* arbol, stContenido dato[], int inicio, int fin);
nodoArbolContenido* insertarArbol (nodoArbolContenido* arbol,nodoArbolContenido* dato);
void dibujarArbol(nodoArbolContenido* arbol, int nivel);


#endif // ARBOLES_H_INCLUDED
