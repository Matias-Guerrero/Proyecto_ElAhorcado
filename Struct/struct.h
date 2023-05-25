#ifndef STRUCTS_H
#define STRUCTS_H

#include "../Map/Map.h"
#include "../List/list.h"

typedef struct {
    char palabra[50];
    // char pista[50];
    int nivel;
} Palabra;

typedef struct {
    char palabraSecreta[50];
    char palabraActual[50];
    int nivel;
    int intentosRestantes;
    List *letrasJugadas;
} Nivel;

typedef struct {
    char nombre[50];
    int puntos;
    int nivel;
    Map *palabrasJugadas;
} Jugador;

#endif //STRUCTS_H