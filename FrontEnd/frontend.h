#ifndef FRONTEND_H
#define FRONTEND_H

#include "../BackEnd/backend.h"
#include "../Struct/struct.h"

// FUNCIONES DE LA INTERFAZ DEL JUEGO

void gotoxy(int x, int y);

void ocultarCursor();

void cargando(int duracion);

// void cuadro();

void menu(Jugador *jugador);

#endif // FRONTEND_H