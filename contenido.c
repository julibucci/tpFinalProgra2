#include "contenido.h"
#include <stdio.h>
#include <stdlib.h>
#define ARCHI_CONT "cont.dat"
#include <conio.h>
#define ESC 27

/// CARGO UN CONTENIDO
stContenido ingresarCont(int id)
{
    stContenido c;


    c.idContenido=id+100;


    printf("\nTITULO: \n");
    fflush(stdin);
    gets(c.titulo);

    printf("Publique un texto con un maximo de 300 caracteres: ");
    fflush(stdin);
    gets(c.descripcion);

    int opcionCategoria;
    printf("Seleccione la categoria:\n");
    printf("1) Terror\n");
    printf("2) Amor\n");
    printf("3) Suspenso\n");
    printf("4) Drama\n");
    printf("Ingrese el numero de la categoria: ");
    scanf("%d", &opcionCategoria);

    switch (opcionCategoria)
    {
    case 1:
        strcpy(c.categoria, "Terror");
        break;
    case 2:
        strcpy(c.categoria, "Amor");
        break;
    case 3:
        strcpy(c.categoria, "Suspenso");
        break;
    case 4:
        strcpy(c.categoria, "Drama");
        break;
    default:
        strcpy(c.categoria, "Otra");
        break;
    }


    c.likes=0;
    c.puntosPorCompartir=0;
    c.activo=1;

    return c;

}

/// MUESTRO UN CONTENIDO
void mostrarContenido(stContenido c)
{
    printf ("\n%s",c.titulo);
    printf("\n----------------------");
    printf ("\n%s",c.descripcion);
    printf("\n----------------------");

    printf ("\nLike: %d",c.likes);

}

/// MUESTRO EL CONTENIDO DEL ADMIN
void mostrarContenidoAdmin(stContenido c)
{
    printf ("\n%s",c.titulo);
    printf("\n----------------------");
    printf ("\n%s",c.categoria);
    printf("\n----------------------");
    printf ("\n%s",c.descripcion);
    printf("\n----------------------");


    printf ("\nLike: %d",c.likes);


    printf("\n================================\n");


}

/// CARGA DE UN CONTENIDO EN ARCHIVO
void cargaArchiUnCont(char nombreArchivo[],int id)
{
    FILE* archi= fopen(nombreArchivo, "ab");
    stContenido contenido;
    if(archi!=NULL)
    {
        contenido= ingresarCont(id);
        fwrite(&contenido,sizeof(stContenido),1, archi);
    }
    fclose(archi);

}

/// MUESTRO CONTENIDO DEL ARCHIVO
void mostrarContenidosEnArchivo(char nombreArchivo[])
{
    FILE *archivo = fopen(nombreArchivo, "rb");

    stContenido contenido;
    if(archivo != NULL)
    {
        while (fread(&contenido, sizeof(stContenido), 1, archivo) == 1)
        {
            printf("ID de Contenido: %d\n", contenido.idContenido);
            printf("Título: %s\n", contenido.titulo);
            printf("Descripción: %s\n", contenido.descripcion);
            printf("Categoría: %s\n", contenido.categoria);
            printf("Likes: %d\n", contenido.likes);
            printf("Puntos por Compartir: %d\n", contenido.puntosPorCompartir);
            printf("Activo: %s\n", contenido.activo);
            printf("========================================\n");

        }

    }

    fclose(archivo);
}


/// Función para cargar el contenido del archivo en un arreglo
int cargarContenidosDesdeArchivo(char nombreArchivo[], stContenido dato[])
{
    FILE* archivo = fopen(nombreArchivo, "rb");
    int cantidadElementos = 0;

    if(archivo != NULL)
    {
        while (cantidadElementos < 100 && fread(&dato[cantidadElementos], sizeof(stContenido), 1, archivo) == 1)
        {
            cantidadElementos++;
        }

        fclose(archivo);
    }
    return cantidadElementos;
}


/// Función para dar de alta un contenido en el archivo
void altaContenido(FILE *archivo, stContenido contenido)
{
    fseek(archivo, 0, SEEK_END);// Ir al final del archivo
    fwrite(&contenido, sizeof(stContenido), 1, archivo);
}

/// Función para dar de baja un contenido en el archivo
void bajaContenido(FILE *archivo, int id)
{
    FILE *tempFile = fopen("temp.dat", "wb");
    stContenido contenido;

    while (fread(&contenido, sizeof(stContenido), 1, archivo) == 1)
    {
        if (contenido.idContenido != id)
        {
            fwrite(&contenido, sizeof(stContenido), 1, tempFile);
        }
    }

    fclose(archivo);
    fclose(tempFile);

    remove("contenidos.dat");
    rename("temp.dat", "contenidos.dat");
}

/// Función para modificar un contenido en el archivo
void modificarContenido(char nombreArchivo, int id, stContenido nuevoContenido)
{
    FILE* archivo = fopen(nombreArchivo,"rb");
    fseek(archivo, 0, SEEK_SET);
    stContenido contenido;

    while (fread(&contenido, sizeof(stContenido), 1, archivo) == 1)
    {
        if (contenido.idContenido == id)
        {
            fseek(archivo, -sizeof(stContenido), SEEK_CUR);
            fwrite(&nuevoContenido, sizeof(stContenido), 1, archivo);
            break;
        }
    }
}

/// Función para consultar un contenido por ID
void consultarContenido(char nombreArchivo, int id)
{
    stContenido contenido;
    FILE* archivo = fopen(nombreArchivo,"rb");

    fseek(archivo, 0, SEEK_SET);
    while (fread(&contenido, sizeof(stContenido), 1, archivo) == 1)
    {
        if (contenido.idContenido == id)
        {
            printf("ID: %d\n", contenido.idContenido);
            printf("Titulo: %s\n", contenido.titulo);
            printf("Descripcion: %s\n", contenido.descripcion);
            printf("Categoria: %s\n", contenido.categoria);
            printf("Likes: %d\n", contenido.likes);
            printf("Puntos por compartir: %d\n", contenido.puntosPorCompartir);
            printf("Activo: %s\n", contenido.activo);

        }
    }

    printf("Contenido no encontrado.\n");
}

/// Funcion para listar todos los contenidos activos
void listarContenidos(FILE *archivo)
{
    stContenido contenido;

    fseek(archivo, 0, SEEK_SET);
    while (fread(&contenido, sizeof(stContenido), 1, archivo) == 1)
    {
        if (contenido.activo)
        {
            printf("ID: %d\n", contenido.idContenido);
            printf("Titulo: %s\n", contenido.titulo);
            printf("Categoria: %s\n", contenido.categoria);
            printf("Likes: %d\n", contenido.likes);
            printf("Puntos por compartir: %d\n", contenido.puntosPorCompartir);
            printf("----\n");
        }
    }
}

///Paso de archivo a arreglo --> insercion por titulo -> paso a arbol
void insertarPorTitulo(stContenido contenido[], int numElementos, stContenido nuevoContenido)
{
    int i = numElementos - 1;

    while (i >= 0 && strcmp(nuevoContenido.titulo, contenido[i].titulo) < 0)
    {
        contenido[i + 1] = contenido[i];
        i--;
    }

    contenido[i + 1] = nuevoContenido;
    numElementos++;
}

int leerContenidoDesdeArchivo(char nombreArchivo, stContenido contenido[], int maxElementos)
{
    FILE *archivo = fopen(nombreArchivo, "rb");
    int numElementos = 0;
    if(archivo != NULL)
    {
        stContenido temp;


        while (fread(&temp, sizeof(stContenido), 1, archivo) == 1 && numElementos < maxElementos)
        {
            insertarPorTitulo(contenido, &numElementos, temp);
        }

        fclose(archivo);

    }

    return numElementos;
}

int contarContenidosEnArchivo(char nombreArchivo[])
{
    int contador = 0;
    FILE *archivo = fopen(nombreArchivo, "rb");
    if (archivo != NULL)
    {
        stContenido contenido;

        while (fread(&contenido, sizeof(stContenido), 1, archivo) == 1)
        {
            contador++;
        }

        fclose(archivo);
    }
    return contador;
}

/// CARGA DE LOS 100 CONTENIDOS EN EL ARCHIVO
void cargarContenidosEnArchi(char nombreArchivo[])
{
    FILE* archi = fopen(nombreArchivo, "wb");
    stContenido contenido;

    if (archi != NULL)
    {

        // Cargar contenido 1
        contenido.idContenido = 1;
        strcpy(contenido.titulo, "Orgullo y prejuicio");
        strcpy(contenido.descripcion, "Una historia de amor y clases sociales en la Inglaterra del siglo XIX.");
        strcpy(contenido.categoria, "Amor");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        // Cargar contenido 2
        contenido.idContenido = 2;
        strcpy(contenido.titulo, "El resplandor");
        strcpy(contenido.descripcion, "Un hombre y su familia se mudan a un hotel aislado en las montañas, pero algo siniestro acecha en el lugar.");
        strcpy(contenido.categoria, "Terror");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        // Cargar contenido 3
        contenido.idContenido = 3;
        strcpy(contenido.titulo, "El codigo Da Vinci");
        strcpy(contenido.descripcion, "Un profesor de Harvard investiga un misterio que podria cambiar la historia de la humanidad.");
        strcpy(contenido.categoria, "Misterio");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        // Cargar contenido 4
        contenido.idContenido = 4;
        strcpy(contenido.titulo, "Romeo y Julieta");
        strcpy(contenido.descripcion, "Una de las tragedias más conocidas de Shakespeare sobre el amor prohibido entre dos jóvenes de familias rivales.");
        strcpy(contenido.categoria, "Amor");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);


// Cargar contenido 5
        contenido.idContenido = 5;
        strcpy(contenido.titulo, "El Exorcista");
        strcpy(contenido.descripcion, "Una niña es poseida por una entidad maligna, y dos sacerdotes intentan expulsar al demonio.");
        strcpy(contenido.categoria, "Terror");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

// Cargar contenido 6
        contenido.idContenido = 6;
        strcpy(contenido.titulo, "Los hombres me explican cosas");
        strcpy(contenido.descripcion, "Un ensayo que aborda el machismo y la condescendencia hacia las mujeres en la sociedad.");
        strcpy(contenido.categoria, "Ensayo");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

// Cargar contenido 7
        contenido.idContenido = 7;
        strcpy(contenido.titulo, "Misery");
        strcpy(contenido.descripcion, "Un escritor es secuestrado por su fan número uno y obligado a escribir para ella.");
        strcpy(contenido.categoria, "Suspense");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

// Cargar contenido 8
        contenido.idContenido = 8;
        strcpy(contenido.titulo, "Cumbres Borrascosas");
        strcpy(contenido.descripcion, "Una historia de pasión y venganza en las brumosas colinas de Yorkshire.");
        strcpy(contenido.categoria, "Amor");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

// Cargar contenido 9
        contenido.idContenido = 9;
        strcpy(contenido.titulo, "El silencio de los corderos");
        strcpy(contenido.descripcion, "Un agente del FBI busca la ayuda de un psicópata encarcelado para atrapar a otro asesino en serie.");
        strcpy(contenido.categoria, "Suspense");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

// Cargar contenido 10
        contenido.idContenido = 10;
        strcpy(contenido.titulo, "El amor en los tiempos del cólera");
        strcpy(contenido.descripcion, "La historia de un amor que perdura a lo largo de décadas, a pesar de los obstáculos.");
        strcpy(contenido.categoria, "Amor");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        // Cargar contenido 11
        contenido.idContenido = 11;
        strcpy(contenido.titulo, "La carretera");
        strcpy(contenido.descripcion, "Un padre y su hijo viajan a través de un mundo postapocalíptico en busca de un lugar seguro.");
        strcpy(contenido.categoria, "Ciencia ficción");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

// Cargar contenido 12
        contenido.idContenido = 12;
        strcpy(contenido.titulo, "Crimen y castigo");
        strcpy(contenido.descripcion, "La historia de Rodion Raskolnikov, un estudiante que comete un asesinato y lucha con su culpa y remordimiento.");
        strcpy(contenido.categoria, "Suspense");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

// Cargar contenido 13
        contenido.idContenido = 13;
        strcpy(contenido.titulo, "1984");
        strcpy(contenido.descripcion, "Una distopía que describe un futuro totalitario en el que el gobierno controla cada aspecto de la vida de las personas.");
        strcpy(contenido.categoria, "Ciencia ficción");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

// Cargar contenido 14
        contenido.idContenido = 14;
        strcpy(contenido.titulo, "Don Quijote de la Mancha");
        strcpy(contenido.descripcion, "La historia del caballero loco Don Quijote y su fiel escudero Sancho Panza mientras emprenden aventuras por toda España.");
        strcpy(contenido.categoria, "Aventuras");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

// Cargar contenido 15
        contenido.idContenido = 15;
        strcpy(contenido.titulo, "Moby-Dick");
        strcpy(contenido.descripcion, "La obsesiva búsqueda de venganza del capitán Ahab contra la ballena blanca, Moby-Dick, en el océano.");
        strcpy(contenido.categoria, "Aventuras");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

// Cargar contenido 16
        contenido.idContenido = 16;
        strcpy(contenido.titulo, "Los juegos del hambre");
        strcpy(contenido.descripcion, "Una saga distópica que sigue a Katniss Everdeen mientras lucha por sobrevivir en un mundo donde los jóvenes son forzados a pelear a muerte en un reality show.");
        strcpy(contenido.categoria, "Ciencia ficción");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

// Cargar contenido 17
        contenido.idContenido = 17;
        strcpy(contenido.titulo, "El Gran Gatsby");
        strcpy(contenido.descripcion, "Una crítica a la sociedad de la década de 1920 a través de la historia del misterioso Jay Gatsby y su amor por Daisy Buchanan.");
        strcpy(contenido.categoria, "Drama");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

// Cargar contenido 18
        contenido.idContenido = 18;
        strcpy(contenido.titulo, "La naranja mecánica");
        strcpy(contenido.descripcion, "La historia de Alex, un joven delincuente y sociópata, y su experiencia con el tratamiento de reeducación.");
        strcpy(contenido.categoria, "Ciencia ficción");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

// Cargar contenido 19
        contenido.idContenido = 19;
        strcpy(contenido.titulo, "Cien años de soledad");
        strcpy(contenido.descripcion, "Un clásico de la literatura latinoamericana que narra la historia de la familia Buendía en el pueblo ficticio de Macondo.");
        strcpy(contenido.categoria, "Realismo mágico");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

// Cargar contenido 20
        contenido.idContenido = 20;
        strcpy(contenido.titulo, "Los pilares de la Tierra");
        strcpy(contenido.descripcion, "La construcción de una catedral en la Inglaterra medieval y las vidas entrelazadas de sus personajes.");
        strcpy(contenido.categoria, "Histórica");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

// Cargar contenido 21
        contenido.idContenido = 21;
        strcpy(contenido.titulo, "La Sombra del Viento");
        strcpy(contenido.descripcion, "Un joven busca respuestas sobre un misterioso autor y su obra, pero se ve envuelto en un peligroso enigma literario.");
        strcpy(contenido.categoria, "Misterio");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

// Cargar contenido 22
        contenido.idContenido = 22;
        strcpy(contenido.titulo, "El Principito");
        strcpy(contenido.descripcion, "Un cuento filosófico sobre un pequeño príncipe que viaja por el universo y aprende lecciones importantes sobre la vida.");
        strcpy(contenido.categoria, "Filosofía");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

// Cargar contenido 23
        contenido.idContenido = 23;
        strcpy(contenido.titulo, "Los miserables");
        strcpy(contenido.descripcion, "La historia de Jean Valjean, un hombre que lucha por redimirse y escapar de la persecución del inspector Javert.");
        strcpy(contenido.categoria, "Drama");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

// Cargar contenido 24
        contenido.idContenido = 24;
        strcpy(contenido.titulo, "Matar un ruiseñor");
        strcpy(contenido.descripcion, "La historia de una niña llamada Scout Finch y su padre, el abogado Atticus Finch, mientras luchan contra la injusticia racial en el sur de Estados Unidos.");
        strcpy(contenido.categoria, "Drama");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

// Cargar contenido 25
        contenido.idContenido = 25;
        strcpy(contenido.titulo, "En busca del tiempo perdido");
        strcpy(contenido.descripcion, "Una novela monumental que explora la memoria, el tiempo y la vida social en la Francia del siglo XIX y principios del siglo XX.");
        strcpy(contenido.categoria, "Literatura clásica");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        // Cargar contenido 26
        contenido.idContenido = 26;
        strcpy(contenido.titulo, "Rayuela");
        strcpy(contenido.descripcion, "Una novela experimental que desafía la estructura convencional y permite múltiples formas de lectura.");
        strcpy(contenido.categoria, "Literatura experimental");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

// Cargar contenido 27
        contenido.idContenido = 27;
        strcpy(contenido.titulo, "El lobo estepario");
        strcpy(contenido.descripcion, "La historia de Harry Haller, un hombre dividido entre su naturaleza humana y su lado lobo.");
        strcpy(contenido.categoria, "Literatura existencialista");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

// Cargar contenido 28
        contenido.idContenido = 28;
        strcpy(contenido.titulo, "Mujer en punto cero");
        strcpy(contenido.descripcion, "La historia de Firdaus, una prisionera que decide enfrentar su destino en una sociedad opresiva.");
        strcpy(contenido.categoria, "Feminismo");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

// Cargar contenido 29
        contenido.idContenido = 29;
        strcpy(contenido.titulo, "La insoportable levedad del ser");
        strcpy(contenido.descripcion, "Una exploración de las vidas entrelazadas de cuatro personajes y sus dilemas existenciales.");
        strcpy(contenido.categoria, "Filosofía");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

// Cargar contenido 30
        contenido.idContenido = 30;
        strcpy(contenido.titulo, "El Perfume");
        strcpy(contenido.descripcion, "La historia de Jean-Baptiste Grenouille, un asesino obsesionado por los olores.");
        strcpy(contenido.categoria, "Misterio");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        // Cargar contenido 31
        contenido.idContenido = 31;
        strcpy(contenido.titulo, "La carretera");
        strcpy(contenido.descripcion, "Un padre y su hijo viajan a través de un mundo postapocalíptico en busca de un lugar seguro.");
        strcpy(contenido.categoria, "Ciencia ficción");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

// Cargar contenido 32
        contenido.idContenido = 32;
        strcpy(contenido.titulo, "Crimen y castigo");
        strcpy(contenido.descripcion, "La historia de Rodion Raskolnikov, un estudiante que comete un asesinato y lucha con su culpa y remordimiento.");
        strcpy(contenido.categoria, "Suspense");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

// Cargar contenido 33
        contenido.idContenido = 33;
        strcpy(contenido.titulo, "Los pilares de la Tierra");
        strcpy(contenido.descripcion, "La construcción de una catedral en la Inglaterra medieval y las vidas entrelazadas de sus personajes.");
        strcpy(contenido.categoria, "Histórica");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

// Cargar contenido 34
        contenido.idContenido = 34;
        strcpy(contenido.titulo, "La naranja mecánica");
        strcpy(contenido.descripcion, "La historia de Alex, un joven delincuente y sociópata, y su experiencia con el tratamiento de reeducación.");
        strcpy(contenido.categoria, "Ciencia ficción");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

// Cargar contenido 35
        contenido.idContenido = 35;
        strcpy(contenido.titulo, "El Gran Gatsby");
        strcpy(contenido.descripcion, "Una crítica a la sociedad de la década de 1920 a través de la historia del misterioso Jay Gatsby y su amor por Daisy Buchanan.");
        strcpy(contenido.categoria, "Drama");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

// Cargar contenido 36
        contenido.idContenido = 36;
        strcpy(contenido.titulo, "La Sombra del Viento");
        strcpy(contenido.descripcion, "Un joven busca respuestas sobre un misterioso autor y su obra, pero se ve envuelto en un peligroso enigma literario.");
        strcpy(contenido.categoria, "Misterio");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

// Cargar contenido 37
        contenido.idContenido = 37;
        strcpy(contenido.titulo, "El Principito");
        strcpy(contenido.descripcion, "Un cuento filosófico sobre un pequeño príncipe que viaja por el universo y aprende lecciones importantes sobre la vida.");
        strcpy(contenido.categoria, "Filosofía");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

// Cargar contenido 38
        contenido.idContenido = 38;
        strcpy(contenido.titulo, "Los miserables");
        strcpy(contenido.descripcion, "La historia de Jean Valjean, un hombre que lucha por redimirse y escapar de la persecución del inspector Javert.");
        strcpy(contenido.categoria, "Drama");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

// Cargar contenido 39
        contenido.idContenido = 39;
        strcpy(contenido.titulo, "Matar un ruiseñor");
        strcpy(contenido.descripcion, "La historia de una niña llamada Scout Finch y su padre, el abogado Atticus Finch, mientras luchan contra la injusticia racial en el sur de Estados Unidos.");
        strcpy(contenido.categoria, "Drama");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

// Cargar contenido 40
        contenido.idContenido = 40;
        strcpy(contenido.titulo, "En busca del tiempo perdido");
        strcpy(contenido.descripcion, "Una novela monumental que explora la memoria, el tiempo y la vida social en la Francia del siglo XIX y principios del siglo XX.");
        strcpy(contenido.categoria, "Literatura clásica");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 41;
        strcpy(contenido.titulo, "En busca del tiempo perdido");
        strcpy(contenido.descripcion, "Una novela monumental que explora la memoria, el tiempo y la vida social en la Francia del siglo XIX y principios del siglo XX.");
        strcpy(contenido.categoria, "Literatura clasica");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 42;
        strcpy(contenido.titulo, "Rayuela");
        strcpy(contenido.descripcion, "Una novela experimental que desafia la estructura convencional y permite multiples formas de lectura.");
        strcpy(contenido.categoria, "Literatura experimental");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 43;
        strcpy(contenido.titulo, "El lobo estepario");
        strcpy(contenido.descripcion, "La historia de Harry Haller, un hombre dividido entre su naturaleza humana y su lado lobo.");
        strcpy(contenido.categoria, "Literatura existencialista");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 44;
        strcpy(contenido.titulo, "Mujer en punto cero");
        strcpy(contenido.descripcion, "La historia de Firdaus, una prisionera que decide enfrentar su destino en una sociedad opresiva.");
        strcpy(contenido.categoria, "Feminismo");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 45;
        strcpy(contenido.titulo, "La insoportable levedad del ser");
        strcpy(contenido.descripcion, "Una exploracion de las vidas entrelazadas de cuatro personajes y sus dilemas existenciales.");
        strcpy(contenido.categoria, "Filosofia");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 46;
        strcpy(contenido.titulo, "Los hombres me explican cosas");
        strcpy(contenido.descripcion, "Un ensayo que aborda el machismo y la condescendencia hacia las mujeres en la sociedad.");
        strcpy(contenido.categoria, "Ensayo");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 47;
        strcpy(contenido.titulo, "El Perfume");
        strcpy(contenido.descripcion, "La historia de Jean-Baptiste Grenouille, un asesino obsesionado por los olores.");
        strcpy(contenido.categoria, "Misterio");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 48;
        strcpy(contenido.titulo, "La carretera");
        strcpy(contenido.descripcion, "Un padre y su hijo viajan a traves de un mundo postapocaliptico en busca de un lugar seguro.");
        strcpy(contenido.categoria, "Ciencia ficcion");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 49;
        strcpy(contenido.titulo, "Crimen y castigo");
        strcpy(contenido.descripcion, "La historia de Rodion Raskolnikov, un estudiante que comete un asesinato y lucha con su culpa y remordimiento.");
        strcpy(contenido.categoria, "Suspense");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 50;
        strcpy(contenido.titulo, "1984");
        strcpy(contenido.descripcion, "Una distopia que describe un futuro totalitario en el que el gobierno controla cada aspecto de la vida de las personas.");
        strcpy(contenido.categoria, "Ciencia ficcion");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 51;
        strcpy(contenido.titulo, "La Ciudad de las Bestias");
        strcpy(contenido.descripcion, "Una aventura en la Amazonia en busca de criaturas miticas.");
        strcpy(contenido.categoria, "Aventuras");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 52;
        strcpy(contenido.titulo, "Los Juegos del Hambre");
        strcpy(contenido.descripcion, "Katniss Everdeen lucha por sobrevivir en un mundo donde los jovenes son forzados a pelear a muerte en un reality show.");
        strcpy(contenido.categoria, "Ciencia ficcion");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 53;
        strcpy(contenido.titulo, "Los Juegos del Hambre: En Llamas");
        strcpy(contenido.descripcion, "La secuela de la lucha de Katniss en los Juegos del Hambre.");
        strcpy(contenido.categoria, "Ciencia ficcion");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 54;
        strcpy(contenido.titulo, "Los Juegos del Hambre: Sinsajo");
        strcpy(contenido.descripcion, "La rebelion contra el Capitolio en el ultimo libro de la trilogia de Los Juegos del Hambre.");
        strcpy(contenido.categoria, "Ciencia ficcion");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 55;
        strcpy(contenido.titulo, "Don Quijote de la Mancha");
        strcpy(contenido.descripcion, "La historia del caballero loco Don Quijote y su fiel escudero Sancho Panza mientras emprenden aventuras por toda Espana.");
        strcpy(contenido.categoria, "Aventuras");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 56;
        strcpy(contenido.titulo, "Moby-Dick");
        strcpy(contenido.descripcion, "La obsesiva búsqueda de venganza del capitán Ahab contra la ballena blanca, Moby-Dick, en el océano.");
        strcpy(contenido.categoria, "Aventuras");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 57;
        strcpy(contenido.titulo, "Los Pilares de la Tierra");
        strcpy(contenido.descripcion, "La construcción de una catedral en la Inglaterra medieval y las vidas entrelazadas de sus personajes.");
        strcpy(contenido.categoria, "Histórica");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 58;
        strcpy(contenido.titulo, "La Sombra del Viento");
        strcpy(contenido.descripcion, "Un joven busca respuestas sobre un misterioso autor y su obra, pero se ve envuelto en un peligroso enigma literario.");
        strcpy(contenido.categoria, "Misterio");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 59;
        strcpy(contenido.titulo, "El Principito");
        strcpy(contenido.descripcion, "Un cuento filosófico sobre un pequeño príncipe que viaja por el universo y aprende lecciones importantes sobre la vida.");
        strcpy(contenido.categoria, "Filosofía");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 60;
        strcpy(contenido.titulo, "Los Miserables");
        strcpy(contenido.descripcion, "La historia de Jean Valjean, un hombre que lucha por redimirse y escapar de la persecución del inspector Javert.");
        strcpy(contenido.categoria, "Drama");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 61;
        strcpy(contenido.titulo, "Matar un ruiseñor");
        strcpy(contenido.descripcion, "La historia de una niña llamada Scout Finch y su padre, el abogado Atticus Finch, mientras luchan contra la injusticia racial en el sur de Estados Unidos.");
        strcpy(contenido.categoria, "Drama");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 62;
        strcpy(contenido.titulo, "En busca del tiempo perdido");
        strcpy(contenido.descripcion, "Una novela monumental que explora la memoria, el tiempo y la vida social en la Francia del siglo XIX y principios del siglo XX.");
        strcpy(contenido.categoria, "Literatura clásica");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 63;
        strcpy(contenido.titulo, "Rayuela");
        strcpy(contenido.descripcion, "Una novela experimental que desafía la estructura convencional y permite múltiples formas de lectura.");
        strcpy(contenido.categoria, "Literatura experimental");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 64;
        strcpy(contenido.titulo, "El lobo estepario");
        strcpy(contenido.descripcion, "La historia de Harry Haller, un hombre dividido entre su naturaleza humana y su lado lobo.");
        strcpy(contenido.categoria, "Literatura existencialista");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 65;
        strcpy(contenido.titulo, "Mujer en punto cero");
        strcpy(contenido.descripcion, "La historia de Firdaus, una prisionera que decide enfrentar su destino en una sociedad opresiva.");
        strcpy(contenido.categoria, "Feminismo");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 66;
        strcpy(contenido.titulo, "La insoportable levedad del ser");
        strcpy(contenido.descripcion, "Una exploración de las vidas entrelazadas de cuatro personajes y sus dilemas existenciales.");
        strcpy(contenido.categoria, "Filosofia");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 67;
        strcpy(contenido.titulo, "Cincuenta sombras de Grey");
        strcpy(contenido.descripcion, "La historia de una relación apasionada y a menudo controvertida entre una joven graduada y un exitoso empresario.");
        strcpy(contenido.categoria, "Romance erótico");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 68;
        strcpy(contenido.titulo, "Los juegos del hambre");
        strcpy(contenido.descripcion, "Una saga distópica que sigue a Katniss Everdeen mientras lucha por sobrevivir en un mundo donde los jóvenes son forzados a pelear a muerte en un reality show.");
        strcpy(contenido.categoria, "Ciencia ficción");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 69;
        strcpy(contenido.titulo, "El Gran Gatsby");
        strcpy(contenido.descripcion, "Una crítica a la sociedad de la década de 1920 a través de la historia del misterioso Jay Gatsby y su amor por Daisy Buchanan.");
        strcpy(contenido.categoria, "Drama");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 70;
        strcpy(contenido.titulo, "La Sombra del Viento");
        strcpy(contenido.descripcion, "Un joven busca respuestas sobre un misterioso autor y su obra, pero se ve envuelto en un peligroso enigma literario.");
        strcpy(contenido.categoria, "Misterio");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 71;
        strcpy(contenido.titulo, "El Principito");
        strcpy(contenido.descripcion, "Un cuento filosófico sobre un pequeño príncipe que viaja por el universo y aprende lecciones importantes sobre la vida.");
        strcpy(contenido.categoria, "Filosofia");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 72;
        strcpy(contenido.titulo, "Los miserables");
        strcpy(contenido.descripcion, "La historia de Jean Valjean, un hombre que lucha por redimirse y escapar de la persecución del inspector Javert.");
        strcpy(contenido.categoria, "Drama");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 73;
        strcpy(contenido.titulo, "Matar un ruiseñor");
        strcpy(contenido.descripcion, "La historia de una niña llamada Scout Finch y su padre, el abogado Atticus Finch, mientras luchan contra la injusticia racial en el sur de Estados Unidos.");
        strcpy(contenido.categoria, "Drama");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 74;
        strcpy(contenido.titulo, "En busca del tiempo perdido");
        strcpy(contenido.descripcion, "Una novela monumental que explora la memoria, el tiempo y la vida social en la Francia del siglo XIX y principios del siglo XX.");
        strcpy(contenido.categoria, "Literatura clasica");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 75;
        strcpy(contenido.titulo, "Rayuela");
        strcpy(contenido.descripcion, "Una novela experimental que desafía la estructura convencional y permite múltiples formas de lectura.");
        strcpy(contenido.categoria, "Literatura experimental");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 76;
        strcpy(contenido.titulo, "El lobo estepario");
        strcpy(contenido.descripcion, "La historia de Harry Haller, un hombre dividido entre su naturaleza humana y su lado lobo.");
        strcpy(contenido.categoria, "Literatura existencialista");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 77;
        strcpy(contenido.titulo, "Mujer en punto cero");
        strcpy(contenido.descripcion, "La historia de Firdaus, una prisionera que decide enfrentar su destino en una sociedad opresiva.");
        strcpy(contenido.categoria, "Feminismo");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 78;
        strcpy(contenido.titulo, "La insoportable levedad del ser");
        strcpy(contenido.descripcion, "Una exploración de las vidas entrelazadas de cuatro personajes y sus dilemas existenciales.");
        strcpy(contenido.categoria, "Filosofia");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 79;
        strcpy(contenido.titulo, "Los hombres me explican cosas");
        strcpy(contenido.descripcion, "Un ensayo que aborda el machismo y la condescendencia hacia las mujeres en la sociedad.");
        strcpy(contenido.categoria, "Ensayo");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 80;
        strcpy(contenido.titulo, "El Perfume");
        strcpy(contenido.descripcion, "La historia de Jean-Baptiste Grenouille, un asesino obsesionado por los olores.");
        strcpy(contenido.categoria, "Misterio");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 81;
        strcpy(contenido.titulo, "La carretera");
        strcpy(contenido.descripcion, "Un padre y su hijo viajan a través de un mundo postapocalíptico en busca de un lugar seguro.");
        strcpy(contenido.categoria, "Ciencia ficción");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 82;
        strcpy(contenido.titulo, "Crimen y castigo");
        strcpy(contenido.descripcion, "La historia de Rodion Raskolnikov, un estudiante que comete un asesinato y lucha con su culpa y remordimiento.");
        strcpy(contenido.categoria, "Suspense");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 83;
        strcpy(contenido.titulo, "Los pilares de la Tierra");
        strcpy(contenido.descripcion, "La construcción de una catedral en la Inglaterra medieval y las vidas entrelazadas de sus personajes.");
        strcpy(contenido.categoria, "Histórica");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 84;
        strcpy(contenido.titulo, "La naranja mecánica");
        strcpy(contenido.descripcion, "La historia de Alex, un joven delincuente y sociópata, y su experiencia con el tratamiento de reeducación.");
        strcpy(contenido.categoria, "Ciencia ficción");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 85;
        strcpy(contenido.titulo, "El Gran Gatsby");
        strcpy(contenido.descripcion, "Una crítica a la sociedad de la década de 1920 a través de la historia del misterioso Jay Gatsby y su amor por Daisy Buchanan.");
        strcpy(contenido.categoria, "Drama");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 86;
        strcpy(contenido.titulo, "La Sombra del Viento");
        strcpy(contenido.descripcion, "Un joven busca respuestas sobre un misterioso autor y su obra, pero se ve envuelto en un peligroso enigma literario.");
        strcpy(contenido.categoria, "Misterio");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 87;
        strcpy(contenido.titulo, "El Principito");
        strcpy(contenido.descripcion, "Un cuento filosófico sobre un pequeño príncipe que viaja por el universo y aprende lecciones importantes sobre la vida.");
        strcpy(contenido.categoria, "Filosofía");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 88;
        strcpy(contenido.titulo, "Los miserables");
        strcpy(contenido.descripcion, "La historia de Jean Valjean, un hombre que lucha por redimirse y escapar de la persecución del inspector Javert.");
        strcpy(contenido.categoria, "Drama");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 89;
        strcpy(contenido.titulo, "Matar un ruiseñor");
        strcpy(contenido.descripcion, "La historia de una niña llamada Scout Finch y su padre, el abogado Atticus Finch, mientras luchan contra la injusticia racial en el sur de Estados Unidos.");
        strcpy(contenido.categoria, "Drama");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 90;
        strcpy(contenido.titulo, "En busca del tiempo perdido");
        strcpy(contenido.descripcion, "Una novela monumental que explora la memoria, el tiempo y la vida social en la Francia del siglo XIX y principios del siglo XX.");
        strcpy(contenido.categoria, "Literatura clásica");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 91;
        strcpy(contenido.titulo, "Rayuela");
        strcpy(contenido.descripcion, "Una novela experimental que desafía la estructura convencional y permite múltiples formas de lectura.");
        strcpy(contenido.categoria, "Literatura experimental");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 92;
        strcpy(contenido.titulo, "El lobo estepario");
        strcpy(contenido.descripcion, "La historia de Harry Haller, un hombre dividido entre su naturaleza humana y su lado lobo.");
        strcpy(contenido.categoria, "Literatura existencialista");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 93;
        strcpy(contenido.titulo, "Mujer en punto cero");
        strcpy(contenido.descripcion, "La historia de Firdaus, una prisionera que decide enfrentar su destino en una sociedad opresiva.");
        strcpy(contenido.categoria, "Feminismo");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 94;
        strcpy(contenido.titulo, "La insoportable levedad del ser");
        strcpy(contenido.descripcion, "Una exploración de las vidas entrelazadas de cuatro personajes y sus dilemas existenciales.");
        strcpy(contenido.categoria, "Filosofía");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 95;
        strcpy(contenido.titulo, "El perfume");
        strcpy(contenido.descripcion, "La historia de Jean-Baptiste Grenouille, un asesino obsesionado por los olores.");
        strcpy(contenido.categoria, "Misterio");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 96;
        strcpy(contenido.titulo, "La carretera");
        strcpy(contenido.descripcion, "Un padre y su hijo viajan a través de un mundo postapocalíptico en busca de un lugar seguro.");
        strcpy(contenido.categoria, "Ciencia ficción");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 97;
        strcpy(contenido.titulo, "Crimen y castigo");
        strcpy(contenido.descripcion, "La historia de Rodion Raskolnikov, un estudiante que comete un asesinato y lucha con su culpa y remordimiento.");
        strcpy(contenido.categoria, "Suspense");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 98;
        strcpy(contenido.titulo, "Los pilares de la Tierra");
        strcpy(contenido.descripcion, "La construcción de una catedral en la Inglaterra medieval y las vidas entrelazadas de sus personajes.");
        strcpy(contenido.categoria, "Histórica");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 99;
        strcpy(contenido.titulo, "La naranja mecánica");
        strcpy(contenido.descripcion, "La historia de Alex, un joven delincuente y sociópata, y su experiencia con el tratamiento de reeducación.");
        strcpy(contenido.categoria, "Ciencia ficción");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        contenido.idContenido = 100;
        strcpy(contenido.titulo, "El Gran Gatsby");
        strcpy(contenido.descripcion, "Una crítica a la sociedad de la década de 1920 a través de la historia del misterioso Jay Gatsby y su amor por Daisy Buchanan.");
        strcpy(contenido.categoria, "Drama");
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;
        fwrite(&contenido, sizeof(stContenido), 1, archi);

        fclose(archi);
        printf("Contenidos cargados correctamente en el archivo.\n");
    }
    else
    {
        printf("Error al abrir el archivo para escritura.\n");
    }
}

