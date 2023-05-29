#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <conio.h>
#include <windows.h>

#include "frontend.h"

/*La función recibe los parámetros x, y
* y situa el cursor en esa posicción */
void gotoxy(int x, int y){
    HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    //Eje invertido, con y = 0 en la primera línea, y > 0 desde la segunda línea en adelante
    pos.Y = y; 
    SetConsoleCursorPosition(consola, pos);
}

/*Función que oculta el cursor. Si tiene dudas con esta existen
* variados sitios en internet de donde obtener documentación*/
void ocultarCursor(){
    HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursInfo;
    cursInfo.dwSize = 2;
    cursInfo.bVisible = FALSE;
    SetConsoleCursorInfo( consola, &cursInfo);
}

// Función para mostrar el título
void mostrarTitulo(int x, int y)
{
    system("cls");
    // Se imprime el titulo en rojo
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    gotoxy(x, y); printf("######## ##             ###    ##     ##  #######  ########   ######     ###    ########   #######  ");
    gotoxy(x, y + 1); printf("##       ##            ## ##   ##     ## ##     ## ##     ## ##    ##   ## ##   ##     ## ##     ## ");
    gotoxy(x, y + 2); printf("##       ##           ##   ##  ##     ## ##     ## ##     ## ##        ##   ##  ##     ## ##     ## ");
    gotoxy(x, y + 3); printf("######   ##          ##     ## ######### ##     ## ########  ##       ##     ## ##     ## ##     ## ");
    gotoxy(x, y + 4); printf("##       ##          ######### ##     ## ##     ## ##   ##   ##       ######### ##     ## ##     ## ");
    gotoxy(x, y + 5); printf("##       ##          ##     ## ##     ## ##     ## ##    ##  ##    ## ##     ## ##     ## ##     ## ");
    gotoxy(x, y + 6); printf("######## ########    ##     ## ##     ##  #######  ##     ##  ######  ##     ## ########   #######  ");

    // Se restablece el color de la consola
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

// Función para mostrar el menú
void mostrarMenu(int opcionSeleccionada) {
    gotoxy(30, 12); printf("%s JUGAR", (opcionSeleccionada == 1) ? "->" : "  ");
    gotoxy(30, 13); printf("%s Ver Puntuaciones", (opcionSeleccionada == 2) ? "->" : "  ");
    gotoxy(30, 14); printf("%s Elegir Idioma", (opcionSeleccionada == 3) ? "->" : "  ");
}

bool cambiarOpcion(int * opcion)
{
    Sleep(150);
    if( GetAsyncKeyState(VK_UP) ){
        *opcion -= 1;

        if(*opcion < 1)
            *opcion = 1;
    }
    if( GetAsyncKeyState(VK_DOWN) ){
        *opcion += 1;

        if(*opcion > 3)
            *opcion = 3;
    }
    if( GetAsyncKeyState(VK_RETURN) ){
        return true;
    }
    if( GetAsyncKeyState(VK_ESCAPE) ){
        exit(0);
    }

    return false;
}

// Función para mostrar el submenú de jugar
void subMenuJugar()
{
    
}

void menu()
{
    int opcionSeleccionada = 1;

    system("cls"); // Limpiar la pantalla
    mostrarTitulo(10, 2);

    while(true)
    {
        while(!cambiarOpcion(&opcionSeleccionada))
        {
            mostrarMenu(opcionSeleccionada);
        }

        switch(opcionSeleccionada)
        {
            case 1:
                // Se llama a la funcion subMenuJugar
                subMenuJugar();

                break;
            case 2:
                // Se llama a la funcion para seleccionar el nivel
                // seleccionarNivel(jugador);

                // Lógica para la opción 2
                gotoxy(30, 20);
                printf("Ha seleccionado cambiar el nivel.");

                gotoxy(30, 22);
                system("pause");

                break;
            case 3:
                // Se llama a la funcion para mostrar el mapa de palabras
                // mostrarMapaPalabras(jugador);

                // Lógica para la opción 3
                gotoxy(30, 20);
                printf("Ha seleccionado mostrar el mapa de palabras.");

                gotoxy(30, 22);
                system("pause");

                break;
        }

        // Se borra las ultima linea de la pantalla
        gotoxy(30, 20);
        printf("                                                        ");
        gotoxy(30, 22);
        printf("                                                        ");

    }
}