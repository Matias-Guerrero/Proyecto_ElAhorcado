#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <windows.h>
#include <time.h>

//====================================================================================================
// Importar header de backend
//====================================================================================================

#include "backend.h"

//====================================================================================================
// Importar librerias de las estructuras de datos
//====================================================================================================
#include "../DataStructures/ArrayList/arraylist.h"
#include "../DataStructures/List/list.h"
#include "../DataStructures/Map/Map.h"

//====================================================================================================
// Importar structs, funciones de frontend y backend
//====================================================================================================
#include "../Struct/struct.h"

//====================================================================================================
// Funciones de backend
//====================================================================================================

// Función para quitar los tildes de una cadena
char* quitar_tildes(char* cadena)
{
    const char *originales = "áéíóúÁÉÍÓÚ"; // cadena de caracteres con tildes
    const char *reemplazos = "aeiouAEIOU"; // cadena de caracteres sin tildes
    char* nueva_cadena = (char*) malloc(strlen(cadena) + 1); // se reserva memoria para la nueva cadena

    if (nueva_cadena == NULL) // si no se pudo reservar memoria, se retorna NULL
    {
        return NULL;
    }

    int j = 0; // indice para la nueva cadena

    for(int i = 0; cadena[i] != '\0'; i++) // se recorre la cadena original
    {   
        // booleanos para saber si el caracter actual tiene tilde y si ya se reemplazó
        bool conTilde = false;
        bool flag = false;

        // se recorre la cadena de caracteres con tildes
        for(int k = 0; originales[k] != '\0'; k++)
        {
            if(cadena[i] == originales[k]) // si el caracter actual tiene tilde
            {
                if(!flag) // si no se ha reemplazado
                {
                    i++;
                }
                else // si ya se reemplazó
                {
                    conTilde = true; // se marca que el caracter actual tiene tilde
                    nueva_cadena[j++] = reemplazos[k/2]; // se agrega el caracter sin tilde a la nueva cadena
                    break; // se sale del ciclo
                }

                flag = true; // se marca que ya se reemplazó
            }
        }

        if(!conTilde) // si el caracter actual no tiene tilde
        {   
            // se agrega el caracter a la nueva cadena
            nueva_cadena[j++] = cadena[i];
        }
    }

    nueva_cadena[j] = '\0'; // se agrega el caracter nulo al final de la nueva cadena
    return nueva_cadena; // se retorna la nueva cadena
}

// Función para buscar una palabra aleatoria
void agregarPalabraAleatoria(Jugador *jugador)
{
    char archivo[20];

    // Se verifica el nivel seleccionado
    switch(jugador->nivel)
    {
        case 3:
            strcpy(archivo, "../DataBase/03.txt");
            break;
        case 4:
            strcpy(archivo, "../DataBase/04.txt");
            break;
        case 5:
            strcpy(archivo, "../DataBase/05.txt");
            break;
        case 6:
            strcpy(archivo, "../DataBase/06.txt");
            break;
        case 7:
            strcpy(archivo, "../DataBase/07.txt");
            break;
        case 8:
            strcpy(archivo, "../DataBase/08.txt");
            break;
        case 9:
            strcpy(archivo, "../DataBase/09.txt");
            break;
        case 10:
            strcpy(archivo, "../DataBase/10.txt");
            break;
    }

    // Se abre el archivo
    FILE *file = fopen(archivo, "r");

    // Se verifica que el archivo exista
    if(file == NULL)
    {
        printf("No se pudo abrir el archivo\n");
        system("pause");
        exit(1);
    }

    // Se inicializa la semilla para generar números aleatorios
    srand(time(NULL));

    // Se crea un buffer para almacenar la palabra
    char buffer[100];

    // Se recorre el archivo
    while(fgets(buffer, 100, file))
    {
        // Se obtiene un número aleatorio
        int aleatorio = rand() % 1000;

        // Se saltan las palabras hasta llegar al número aleatorio
        for(int i = 0; i < aleatorio; i++)
        {
            fgets(buffer, 100, file);
        }

        // Se elimina el salto de linea
        buffer[strlen(buffer) - 1] = '\0';

        // Se obtiene la longitud de la palabra
        int longitud = strlen(buffer);

        // Se verifica que la longitud de la palabra sea igual al nivel seleccionado
        if(longitud == jugador->nivel)
        {
            // Se quita el tilde de la palabra
            char *palabraSinTilde = quitar_tildes(buffer);

            // Se crea una struct para almacenar la palabra
            Palabra *palabra = (Palabra *) malloc(sizeof(Palabra));

            // Se asigna la palabra a la struct
            strcpy(palabra->palabra, palabraSinTilde);

            // Se asigna el nivel a la struct
            palabra->nivel = jugador->nivel;

            // Se agrega la palabra al mapa
            insertMap(jugador->palabrasJugadas, palabra->palabra, palabra);

            // Mostrar Palabra agregada
            system("cls");
            mostrarTitulo(0, 2);
            gotoxy(30, 12);
            printf("Palabra agregada: %s", palabra->palabra);
            gotoxy(30, 13);
            printf("Nivel: %d", palabra->nivel);
            gotoxy(30, 14);
            printf("Presione cualquier tecla para continuar...");
            getch();
            break;
        }
    }

    // Se cierra el archivo
    fclose(file);
}