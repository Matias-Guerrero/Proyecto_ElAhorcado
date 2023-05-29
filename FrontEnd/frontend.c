#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <conio.h>
#include <windows.h>

#include "frontend.h"

// Funcion para resetear teclas presionadas
void resetearTeclas()
{
    while(GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(VK_RETURN))
    {
        Sleep(150);
    }
}

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
void mostrarMenu(int opcionSeleccionada, int maxOpcion)
{
    if(maxOpcion == 3)
    {
        gotoxy(30, 12); printf("%s JUGAR", (opcionSeleccionada == 1) ? "->" : "  ");
        gotoxy(30, 13); printf("%s Ver Puntuaciones", (opcionSeleccionada == 2) ? "->" : "  ");
        gotoxy(30, 14); printf("%s Elegir Idioma", (opcionSeleccionada == 3) ? "->" : "  ");
    }

    if(maxOpcion == 2)
    {
        gotoxy(30, 12); printf("%s Nueva Partida", (opcionSeleccionada == 1) ? "->" : "  ");
        gotoxy(30, 13); printf("%s Cargar Partida", (opcionSeleccionada == 2) ? "->" : "  ");
    }
}

bool cambiarOpcion(int * opcion, int maxOpcion)
{
    Sleep(150);
    if( GetAsyncKeyState(VK_UP) ){
        *opcion -= 1;

        if(*opcion < 1)
            *opcion = 1;
    }
    if( GetAsyncKeyState(VK_DOWN) ){
        *opcion += 1;

        if(*opcion > maxOpcion)
            *opcion = maxOpcion;
    }
    if( GetAsyncKeyState(VK_RETURN) ){
        return true;
    }
    if( GetAsyncKeyState(VK_ESCAPE) && maxOpcion == 3){
        exit(0);
    }

    return false;
}

void limpiarLinea(int y)
{
    int i;

    gotoxy(1, y);
    for (i = 0; i < 120; i++)
    {
        printf(" ");
    }
}

// Función para mostrar el submenú de jugar
void subMenuJugar()
{
    int opcionSeleccionada = 1;

    // Se limpia la pantalla del menú
    limpiarLinea(12);
    limpiarLinea(13);
    limpiarLinea(14);

    while(true)
    {
        while(!cambiarOpcion(&opcionSeleccionada, 2))
        {
            mostrarMenu(opcionSeleccionada, 2);
        }

        switch(opcionSeleccionada)
        {
            case 1:
                // Se llama a la funcion para jugar
                // jugar(jugador);

                // Lógica para la opción 1
                gotoxy(30, 20);
                printf("Ha seleccionado jugar.");

                break;
            case 2:
                // Se llama a la funcion para cargar partida
                // cargarPartida(jugador);

                // Lógica para la opción 2
                gotoxy(30, 20);
                printf("Ha seleccionado cargar partida.");

                break;
        }

        // Limpiar teclas presionadas
        resetearTeclas();

        // Mensaje de pausa
        while(!GetAsyncKeyState(VK_RETURN))
        {
            gotoxy(30, 22);
            printf("Presione ENTER para continuar...");
        }

        // Se limpia las lineas
        limpiarLinea(20);
        limpiarLinea(22);

        break;
    }    
}

void menu()
{
    int opcionSeleccionada = 1;

    system("cls"); // Limpiar la pantalla
    mostrarTitulo(10, 2);

    while(true)
    {
        while(!cambiarOpcion(&opcionSeleccionada, 3))
        {
            mostrarMenu(opcionSeleccionada, 3);
        }

        switch(opcionSeleccionada)
        {
            case 1:
                // Se llama a la funcion subMenuJugar
                subMenuJugar();

                break;
            case 2:
                break;
            case 3:
                break;
        }
    }
}