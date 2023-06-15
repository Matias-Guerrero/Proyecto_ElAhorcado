#ifndef BACKEND_H
#define BACKEND_H

#include "../Struct/struct.h"
#include "../DataStructures/ArrayList/arraylist.h"
#include "../DataStructures/TreeMap/treemap.h"

void agregarPalabraAleatoria(Jugador *jugador, Nivel *nivel);

void guardarPartida(Jugador *jugador, int x, int y);

void cargarPartida(char *nombreJugador, Jugador *jugador, int x, int y);

void obtenerJugadores(ArrayList *jugadores, Jugador *jugador);

void guardarPuntaje(TreeMap *tree, Jugador *player);

void leerPuntajes(TreeMap *arbol_puntajes, Jugador *jugador);

void exportarPuntajes(TreeMap* arbol_puntajes);

#endif // BACKEND_H