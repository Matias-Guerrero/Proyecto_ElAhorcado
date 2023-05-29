#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <windows.h>
#include <time.h> // Para generar números aleatorios

//====================================================================================================
// Importar librerias de las estructuras de datos
//====================================================================================================

#include "DataStructures/ArrayList/arraylist.h"
#include "DataStructures/List/list.h"
#include "DataStructures/Map/Map.h"

//====================================================================================================
// Importar structs, funciones de frontend y backend
//====================================================================================================

#include "Struct/struct.h"
#include "FrontEnd/frontend.h"
#include "BackEnd/backend.h"

/*
  función para comparar claves de tipo string
  retorna 1 si son iguales
*/
int is_equal_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}


// // Función para seleccionar el nivel
// void seleccionarNivel(Jugador *jugador)
// {
//     int opcion;

//     do{
//         // Se muestra el menú de niveles
//         system("cls");
//         mostrarTitulo(0, 2);
//         gotoxy(30, 12);
//         printf("%s Nivel 3", (jugador->nivel == 3) ? "->" : "  ");
//         gotoxy(30, 13);
//         printf("%s Nivel 4", (jugador->nivel == 4) ? "->" : "  ");
//         gotoxy(30, 14);
//         printf("%s Nivel 5", (jugador->nivel == 5) ? "->" : "  ");
//         gotoxy(30, 15);
//         printf("%s Nivel 6", (jugador->nivel == 6) ? "->" : "  ");
//         gotoxy(30, 16);
//         printf("%s Nivel 7", (jugador->nivel == 7) ? "->" : "  ");

//         // Se obtiene la tecla presionada
//         opcion = getch();

//         // Se evalua la tecla presionada
//         switch(opcion)
//         {
//             case 72: // Flecha arriba
//                 if(jugador->nivel > 3)
//                 {
//                     jugador->nivel = jugador->nivel - 1;
//                 }
//                 break;
//             case 80: // Flecha abajo
//                 if(jugador->nivel < 7)
//                 {
//                     jugador->nivel = jugador->nivel + 1;
//                 }
//                 break;
//             case 13: // Enter
//                 return;
//         }
//     } while(opcion != 27); // Mientras no se presione la tecla ESC
// }

// // Función para mostrar el mapa de palabras
// void mostrarMapa(Map *palabras)
// {
//     // Se muestra el mapa
//     system("cls");
    
//     // Se recorre el mapa
//     char *palabra = firstMap(palabras);

//     while(palabra != NULL)
//     {
//         printf("%s\n", palabra);
//         palabra = nextMap(palabras);
//     }

//     // Se espera a que se presione una tecla
//     system("pause");
// }

int main(int argc, const char * argv[])
{

    //==================== JUGADOR Y MAPA DE PALABRAS ====================

    // Se crea una struct para almacenar el jugador
    Jugador *jugador = (Jugador *) malloc(sizeof(Jugador));

    // Se inicializa el jugador
    jugador->puntos = 0;
    jugador->nivel = 5;
    strcpy(jugador->nombre, "JugadorPrueba");

    // Se crea un mapa para almacenar las palabras del jugador
    jugador->palabrasJugadas = createMap(is_equal_string);

    //==================== MENU INTERACTIVO ====================

    // Se define el tamaño de la pantalla
    system("mode con: cols=120 lines=25");

    ocultarCursor();

    menu();

    return 0;
}