#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#include "frontend.h"
#include "../BackEnd/backend.h"
#include "../Struct/struct.h"

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

void moverCursor(int x, int y)
{
    printf("\033[%d;%df", y, x);
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

void continuar()
{
    // Limpiar teclas presionadas
    resetearTeclas();

    // Mensaje de pausa
    while(!GetAsyncKeyState(VK_RETURN))
    {
        gotoxy(30, 22);
        printf("Presione ENTER para continuar...");
    }
}

void limpiarLinea(int x, int y)
{
    gotoxy(x, y);
 
    for(int i = 0 + x; i < 115; i++)
    {
        printf(" ");
    }
}

// Función para mostrar el título
void mostrarTitulo(int x, int y)
{
    // Se imprime el titulo en rojo
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    /***
     *     _____  _    ___   _                                    _        
     *    |  ___|| |  / _ \ | |                                  | |       
     *    | |__  | | / /_\ \| |__    ___   _ __   ___   __ _   __| |  ___  
     *    |  __| | | |  _  || '_ \  / _ \ | '__| / __| / _` | / _` | / _ \ 
     *    | |___ | | | | | || | | || (_) || |   | (__ | (_| || (_| || (_) |
     *    \____/ |_| \_| |_/|_| |_| \___/ |_|    \___| \__,_| \__,_| \___/ 
     *                                                                     
     *                                                                     
     */

    /***
    *gotoxy(x, y);     printf(" _____  _    ___   _                                    _        ");
    *gotoxy(x, y + 1); printf("|  ___|| |  / _ \\ | |                                  | |       ");
    *gotoxy(x, y + 2); printf("| |__  | | / /_\\ \\| |__    ___   _ __   ___   __ _   __| |  ___  ");
    *gotoxy(x, y + 3); printf("|  __| | | |  _  || '_ \\  / _ \\ | '__| / __| / _` | / _` | / _ \\ ");
    *gotoxy(x, y + 4); printf("| |___ | | | | | || | | || (_) || |   | (__ | (_| || (_| || (_) |");
    *gotoxy(x, y + 5); printf("\\____/ |_| \\_| |_/|_| |_| \\___/ |_|    \\___| \\__,_| \\__,_| \\___/ ");
    *gotoxy(x, y + 6); printf("                                                                 ");
    */

    /***
     *#######  ####                ###     ##  ##   #####   ######     ####     ###    #####     #####
     *##   #   ##                ## ##    ##  ##  ### ###   ##  ##   ##  ##   ## ##    ## ##   ### ###
     *##       ##               ##   ##   ##  ##  ##   ##   ##  ##  ##       ##   ##   ##  ##  ##   ##
     *####     ##               ##   ##   ######  ##   ##   #####   ##       ##   ##   ##  ##  ##   ##
      ##       ##               #######   ##  ##  ##   ##   ## ##   ##       #######   ##  ##  ##   ##
      ##   #   ##  ##           ##   ##   ##  ##  ### ###   ## ##    ##  ##  ##   ##   ## ##   ### ###
     #######  #######           ##   ##   ##  ##   #####   #### ##    ####   ##   ##  #####     #####


    */

   gotoxy(x, y);     printf("#######  ####             ###     ##  ##   #####   ######    ####     ###    #####    #####");
   gotoxy(x, y + 1); printf("##   #   ##              ## ##    ##  ##  ### ###  ##  ##   ##  ##   ## ##   ## ##   ### ###");
   gotoxy(x, y + 2); printf("##       ##             ##   ##   ##  ##  ##   ##  ##  ##  ##       ##   ##  ##  ##  ##   ##");
   gotoxy(x, y + 3); printf("####     ##             ##   ##   ######  ##   ##  #####   ##       ##   ##  ##  ##  ##   ##");
   gotoxy(x, y + 4); printf("##       ##             #######   ##  ##  ##   ##  ## ##   ##       #######  ##  ##  ##   ##");
   gotoxy(x, y + 5); printf("##   #   ##  ##         ##   ##   ##  ##  ### ###  ## ##    ##  ##  ##   ##  ## ##   ### ###");
   gotoxy(x, y + 6); printf("#######  #######        ##   ##   ##  ##   #####  #### ##    ####   ##   ##  #####    #####");
    


    // Se restablece el color de la consola
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void cuadro(int x1, int y1, int x2, int y2)
{
    int i;

    // Se dibuja el cuadro
    for (i = x1; i < x2; i++) // Lineas horizontales
    {
        gotoxy(i, y1); printf("%c", 205);
        gotoxy(i, y2 - 1); printf("%c", 205);
    }

    for (i = y1; i < y2; i++) // Lineas verticales
    {
        gotoxy(x1, i); printf("%c", 186);
        gotoxy(x2 - 1, i); printf("%c", 186);
    }

    gotoxy(x1, y1); printf("%c", 201);
    gotoxy(x1, y2 - 1); printf("%c", 200);
    gotoxy(x2 - 1, y1); printf("%c", 187);
    gotoxy(x2 - 1, y2 - 1); printf("%c", 188);
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

void mostrarAhorcado(int intentos)
{
    /* Se muestra el ahorcado
    gotoxy(2, 3); printf("     ___________");
    gotoxy(2, 4); printf("     |         |");
    gotoxy(2, 5); printf("     |         |");
    gotoxy(2, 6); printf("     |         %c", (intentos > 0) ? 'O' : ' ');
    gotoxy(2, 7); printf("     |        %c%c%c", (intentos > 1) ? '/' : ' ', (intentos > 2) ? '|' : ' ', (intentos > 3) ? '\\' : ' ');
    gotoxy(2, 8); printf("     |        %c %c", (intentos > 4) ? '/' : ' ', (intentos > 5) ? '\\' : ' ');
    gotoxy(2, 9); printf("     |");
    gotoxy(2, 10); printf("     |");
    gotoxy(2, 11); printf("     |");
    gotoxy(2, 12); printf("    _|___");
    gotoxy(2, 13); printf("");
    */
    
/*
  *    _______
  *   |/      |
  *   |      (_)
  *   |      \|/
  *   |       |
  *   |      / \
  *   |
  *  _|___

*/


//Se muestra el ahorcado
gotoxy(2, 3); printf("    _______");
gotoxy(2, 4); printf("   |/      |");
gotoxy(2, 5); printf("   |      %c%c%c", (intentos > 0) ? '(' : ' ', (intentos > 1) ? '_' : ' ', (intentos > 2) ? ')' : ' ');
gotoxy(2, 6); printf("   |      %c%c%c", (intentos > 3) ? '\\' : ' ', (intentos > 4) ? '|' : ' ', (intentos > 5) ? '/' : ' ');
gotoxy(2, 7); printf("   |       %c", (intentos > 6) ? '|' : ' ');
gotoxy(2, 8); printf("   |      %c %c", (intentos > 7) ? '/' : ' ', (intentos > 8) ? '\\' : ' ');
gotoxy(2, 9); printf("   |");
gotoxy(2, 10); printf("   |");
gotoxy(2, 11); printf("   |");
gotoxy(2, 12); printf("  _|___");


   


}

void cargando(int duracion)
{
    // Se limpia la pantalla
    system("cls");

    // Se hace el cuadro
    cuadro(1, 0, 119, 25);

    // Se inicializa la variable para mostrar el ahorcado
    int j = 0;

    // Se inicializa la variable para la duracion de cada mensaje
    int milisegundos = 250;

    // Se hace un bucle para mostrar el mensaje de cargando
    for(int i = 0; i < duracion; i++)
    {
        gotoxy(30, 12); printf("Cargando");
        mostrarAhorcado(j);
        j++;
        Sleep(milisegundos);
        gotoxy(30, 12); printf("Cargando.");
        mostrarAhorcado(j);
        j++;
        Sleep(milisegundos);
        gotoxy(30, 12); printf("Cargando..");
        mostrarAhorcado(j);
        j++;
        Sleep(milisegundos);
        gotoxy(30, 12); printf("Cargando...");
        mostrarAhorcado(j);
        j++;
        Sleep(milisegundos);

        // Se limpia la linea anterior
        limpiarLinea(30, 12);
    }
}

void mostrarJuego(int x, int y)
{
    gotoxy(x, y); printf("  Letras usadas ");
    gotoxy(x, y + 1); printf(" ___________________");
    gotoxy(x, y + 2); printf("|                   |");
    gotoxy(x, y + 3); printf("|                   |");
    gotoxy(x, y + 4); printf("|___________________|");

}

// Funcion Jugar
void jugar(Jugador *jugador)
{
    // Se crea una estructura para guardar el nivel
    Nivel *nivel = (Nivel *)malloc(sizeof(Nivel));

    // Se inicializa el nivel
    nivel->nivel = jugador->nivel;

    // Se llama a la funcion para agregar una palabra aleatoria
    agregarPalabraAleatoria(jugador, nivel);

    // Se limpia la pantalla
    system("cls");

    // Se muestra el cuadro
    cuadro(1, 0, 119, 25);

    // Se muestra el ahorcado con la palabra con guiones
    // for(int i = 0; i < 7; i++)
    // {
    //     mostrarAhorcado(i);
        
    //     Sleep(100);
    // }

    mostrarAhorcado(9); 

    mostrarJuego(70, 10);

    // Se muestra la palabra secreta
    gotoxy(30, 12); printf("La palabra secreta es: %s", nivel->palabraSecreta);

    // Se muestra la palabra del mapa del jugador
    

    // Se muestra el mensaje de pausa
    continuar();
}

// Funcion para nuevo juego
void nuevoJuego(Jugador *jugador)
{
    // Se limpia la pantalla del menú
    limpiarLinea(30, 12);
    limpiarLinea(30, 13);

    // Se crea una variable para guardar el nombre del jugador
    char nombre[50];

    // // Se obtiene el nombre del jugador
    // gotoxy(30, 12); printf("Ingrese su nombre: ");

    // // Se guarda el nombre del jugador
    // scanf("%s", nombre);

    // // Se limpia la linea anterior
    // limpiarLinea(12);

    // Se guarda el nombre del jugador
    strcpy(jugador->nombre, "Jugador Prueba");

    // Se inicializa el nivel y los puntos del jugador
    jugador->nivel = 1;
    jugador->puntos = 0;

    // Se muestra el mensaje de bienvenida
    gotoxy(30, 14); printf("Bienvenido %s", jugador->nombre);
    
    // Mostramos los datos del jugador
    gotoxy(30, 16); printf("Nivel: %d", jugador->nivel);
    gotoxy(30, 17); printf("Puntos: %d", jugador->puntos);

    // Se muestra el mensaje de pausa
    continuar();

    cargando(2);

    jugar(jugador);

}

// Función para mostrar el submenú de jugar
void subMenuJugar(Jugador *jugador)
{
    int opcionSeleccionada = 1;

    // Se limpia la pantalla del menú
    limpiarLinea(30, 12);
    limpiarLinea(30, 13);
    limpiarLinea(30, 14);

    while(true)
    {
        while(!cambiarOpcion(&opcionSeleccionada, 2))
        {
            mostrarMenu(opcionSeleccionada, 2);
        }

        switch(opcionSeleccionada)
        {
            case 1:
                nuevoJuego(jugador);               

                break;
            case 2:
                // Se llama a la funcion para cargar partida
                // cargarPartida(jugador);

                // Lógica para la opción 2
                gotoxy(30, 20);
                printf("Ha seleccionado cargar partida.");

                // Se muestra el mensaje de pausa
                continuar();

                break;
        }

        // Se limpia las lineas
        limpiarLinea(30, 20);
        limpiarLinea(30, 22);

        break;
    }    
}

void menu(Jugador *jugador)
{
    while(true)
    {
        int opcionSeleccionada = 1;

        system("cls"); // Limpiar la pantalla
        cuadro(1, 0, 119, 25); // Se dibuja el cuadro
        mostrarAhorcado(7); // Se muestra el ahorcado
        mostrarTitulo(22, 4);

        while(!cambiarOpcion(&opcionSeleccionada, 3))
        {
            mostrarMenu(opcionSeleccionada, 3);
        }

        switch(opcionSeleccionada)
        {
            case 1:
                // Se llama a la funcion subMenuJugar
                subMenuJugar(jugador);

                break;
            case 2:
                break;
            case 3:
                break;
        }
    }
}