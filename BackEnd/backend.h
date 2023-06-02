#ifndef BACKEND_H
#define BACKEND_H

#include "../Struct/struct.h"
#include "../DataStructures/ArrayList/arraylist.h"

void agregarPalabraAleatoria(Jugador *jugador, Nivel *nivel);

void guardarPartida(Jugador *jugador, int x, int y);

void cargarPartida(char *nombreJugador, Jugador *jugador, int x, int y);

void obtenerJugadores(ArrayList *jugadores);

#endif // BACKEND_H