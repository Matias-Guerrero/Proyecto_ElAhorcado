#ifndef BACKEND_H
#define BACKEND_H

#include "../Struct/struct.h"

void agregarPalabraAleatoria(Jugador *jugador, Nivel *nivel, int idiomaElegido);

void guardarPartida(Jugador *jugador, int x, int y);

void cargarPartida(const char *nombreJugador, Jugador *jugador, int x, int y);

#endif // BACKEND_H