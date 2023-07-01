#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>

//====================================================================================================
// Importar librerias de las estructuras de datos
//====================================================================================================

#include "DataStructures/ArrayList/arraylist.h"
#include "DataStructures/List/list.h"
#include "DataStructures/Map/Map.h"
#include "DataStructures/TreeMap/treemap.h"

//====================================================================================================
// Importar structs, funciones de frontend y backend
//====================================================================================================

#include "Struct/struct.h"
#include "FrontEnd/frontend.h"
#include "BackEnd/backend.h"

// Función para comparar dos enteros
int lower_than_int(void * key1, void * key2)
{
    if((int*) key1 < (int*) key2) return 1;
    return 0;
}


int main(int argc, const char * argv[])
{
    //====================================================================================================
    // SE INICIA UN JUGADOR
    //====================================================================================================

    Jugador *jugador = (Jugador *)malloc(sizeof(Jugador));

    // Se inicializa el idioma en español
    jugador->idioma = 1;

    // Se inicializa la bandera de subir nivel en falso
    jugador->flagSubirNivel = false;

    //====================================================================================================
    // SE INICIA UN ARBOL Y SE LEEN LOS PUNTAJES YA EXISTENTES
    //====================================================================================================

    TreeMap *arbol_puntajes = createTreeMap(lower_than_int);

    leerPuntajes(arbol_puntajes, jugador);

    //====================================================================================================
    // MENU INTERACTIVO
    //====================================================================================================

    // Se define el tamaño de la pantalla
    system("mode con: cols=120 lines=25");

    ocultarCursor();

    menu(jugador, arbol_puntajes);

    exportarPuntajes(arbol_puntajes);

    return 0;
}