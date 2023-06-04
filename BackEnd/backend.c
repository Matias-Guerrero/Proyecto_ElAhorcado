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
#include "../FrontEnd/frontend.h"

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
void agregarPalabraAleatoria(Jugador *jugador, Nivel *nivel, int idiomaElegido)
{   
    if(idiomaElegido == 1)
    {
        char archivo[20];

        int totalPalabras = 100;

        // Se verifica el nivel seleccionado
        switch(jugador->nivel)
        {
            case 1:
                strcpy(archivo, "DataBase/03.txt");
                totalPalabras = 104;
                break;
            case 2:
                strcpy(archivo, "DataBase/04.txt");
                totalPalabras = 407;
                break;
            case 3:
                strcpy(archivo, "DataBase/05.txt");
                totalPalabras = 1007;
                break;
            case 4:
                strcpy(archivo, "DataBase/06.txt");
                totalPalabras = 766;
                break;
            case 5:
                strcpy(archivo, "DataBase/07.txt");
                break;
            case 6:
                strcpy(archivo, "DataBase/08.txt");
                break;
            case 7:
                strcpy(archivo, "DataBase/09.txt");
                break;
            case 8:
                strcpy(archivo, "DataBase/10.txt");
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
            int aleatorio = rand() % totalPalabras;

            // Se saltan las palabras hasta llegar al número aleatorio
            for(int i = 0; i < aleatorio; i++)
            {
                fgets(buffer, 100, file);
            }

            // Se elimina el salto de linea
            buffer[strlen(buffer) - 1] = '\0';

            // Se crea una struct para almacenar la palabra
            Palabra *palabra = (Palabra *) malloc(sizeof(Palabra));

            // Se asigna la palabra a la struct
            strcpy(palabra->palabra, buffer);

            // Se asigna el nivel a la struct
            palabra->nivel = jugador->nivel;

            // Se verifica que la palabra no haya sido jugada
            if(searchMap(jugador->palabrasJugadas, palabra->palabra) == NULL)
            {
                // Se agrega la palabra al mapa
                insertMap(jugador->palabrasJugadas, palabra->palabra, palabra);

                // Se asigna la palabra secreta
                strcpy(nivel->palabraSecreta, buffer);

                break;
            }
            else
            {
                // Se vuelven al inicio del archivo
                rewind(file);
            }
        }

        // Se cierra el archivo
        fclose(file);
    }
    else if (idiomaElegido == 2)
    {
        char archivo[20];

        int totalPalabras = 100;

        // Se verifica el nivel seleccionado
        switch(jugador->nivel)
        {
            case 1:
                strcpy(archivo, "WordBank/03_English.txt");
                totalPalabras = 171;
                break;
            case 2:
                strcpy(archivo, "WordBank/04_English.txt");
                totalPalabras = 69;
                break;
            case 3:
                strcpy(archivo, "WordBank/05_English.txt");
                totalPalabras = 488;
                break;
            case 4:
                strcpy(archivo, "WordBank/06_English.txt");
                totalPalabras = 140;
                break;
            case 5:
                strcpy(archivo, "WordBank/07_English.txt");
                totalPalabras = 500;
                break;
            case 6:
                strcpy(archivo, "WordBank/08_English.txt");
                totalPalabras = 500;
                break;
            case 7:
                strcpy(archivo, "WordBank/09_English.txt");
                totalPalabras = 95;
                break;
            case 8:
                strcpy(archivo, "WordBank/10_English.txt");
                totalPalabras = 100;
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
            int aleatorio = rand() % totalPalabras;

            // Se saltan las palabras hasta llegar al número aleatorio
            for(int i = 0; i < aleatorio; i++)
            {
                fgets(buffer, 100, file);
            }

            // Se elimina el salto de linea
            buffer[strlen(buffer) - 1] = '\0';

            // Se crea una struct para almacenar la palabra
            Palabra *palabra = (Palabra *) malloc(sizeof(Palabra));

            // Se asigna la palabra a la struct
            strcpy(palabra->palabra, buffer);

            // Se asigna el nivel a la struct
            palabra->nivel = jugador->nivel;

            // Se verifica que la palabra no haya sido jugada
            if(searchMap(jugador->palabrasJugadas, palabra->palabra) == NULL)
            {
                // Se agrega la palabra al mapa
                insertMap(jugador->palabrasJugadas, palabra->palabra, palabra);

                // Se asigna la palabra secreta
                strcpy(nivel->palabraSecreta, buffer);

                break;
            }
            else
            {
                // Se vuelven al inicio del archivo
                rewind(file);
            }
        }

        // Se cierra el archivo
        fclose(file);
        }
    
}

void guardarPartida(Jugador *jugador, int x, int y)
{
    // Abrir el archivo de guardado
    FILE *archivo = fopen("partida_guardada.txt", "r");

    // Verificar si el archivo existe
    if (archivo != NULL)
    {
        // El archivo existe, verificar si el jugador ya existe
        char nombre[50];

        // Recorrer el archivo
        while (fgets(nombre, sizeof(nombre), archivo))
        {
            // Si el nombre del jugador es igual al nombre del archivo, el jugador ya existe
            if (strcmp(nombre, jugador->nombre) == 0)
            {
                // Se cierra el archivo
                fclose(archivo);

                // Se abre el archivo en modo escritura al inicio
                archivo = fopen("partida_guardada.txt", "w");

                break;
            }
        }
    }
    else // El archivo no existe
    {
        // Se abre el archivo en modo escritura al final
        archivo = fopen("partida_guardada.txt", "a");
    }

    // Verificar si se pudo abrir el archivo
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo de guardado.\n");
        return;
    }

    fprintf(archivo, "Nombre: %s\n", jugador->nombre);
    fprintf(archivo, "Puntos: %d\n", jugador->puntos);
    fprintf(archivo, "Nivel: %d\n", jugador->nivel);
    fprintf(archivo, "\n");  // Agregar un salto de línea para separar los datos del siguiente jugador

    fclose(archivo);

    // Se muestra un mensaje de confirmación
    gotoxy(x, y); printf("Partida guardada exitosamente.");
}

void cargarPartida(const char *nombreJugador, Jugador *jugador, int x, int y)
{
    // Abrir el archivo de guardado
    FILE *archivo = fopen("partida_guardada.txt", "r");

    // Verificar si el archivo existe
    if (archivo == NULL)
    {
        // El archivo no existe, mostrar un mensaje de error
        gotoxy(x, y); printf("No se encontró ninguna partida guardada.\n");
        
        return;
    }

    // Se crea una variable para almacenar el nombre del jugador y una variable para saber si el jugador fue encontrado
    char nombre[50];
    bool encontrado = false;

    // Recorrer el archivo
    while(fgets(nombre, sizeof(nombre), archivo))
    {
        // Eliminar el salto de línea del final
        nombre[strcspn(nombre, "\n")] = '\0';

        // Verificar si el nombre del jugador es igual al nombre del archivo
        if(strcmp(nombre, nombreJugador) == 0)
        {
            // El jugador fue encontrado, cargar los datos
            encontrado = true;
            strcpy(jugador->nombre, nombreJugador);

            // Leer los demás datos del jugador
            fscanf(archivo, "Puntos: %d\n", &jugador->puntos);
            fscanf(archivo, "Nivel: %d\n", &jugador->nivel);

            // Saltar la línea vacía
            fgets(nombre, sizeof(nombre), archivo);
            break;
        }
    }

    // Cerrar el archivo
    fclose(archivo);

    // Verificar si el jugador fue encontrado
    if (!encontrado)
    {
        // El jugador no fue encontrado, mostrar un mensaje de error
        gotoxy(x, y); printf("No se encontró ninguna partida para el jugador '%s'.\n", nombreJugador);
        
        return;
    }
}