#ifndef FRONTEND_H
#define FRONTEND_H

#include "../BackEnd/backend.h"
#include "../Struct/struct.h"
#include "../DataStructures/TreeMap/treemap.h"
// FUNCIONES DE LA INTERFAZ DEL JUEGO

void gotoxy(int x, int y);

void ocultarCursor();

void cargando(int duracion, Jugador *jugador);

void pause(int x, int y, char *mensaje);

// void cuadro();

void menu(Jugador *jugador, TreeMap *arbol_puntajes);

#endif // FRONTEND_H