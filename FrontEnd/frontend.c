#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#include "frontend.h"
#include "../BackEnd/backend.h"
#include "../Struct/struct.h"
#include "../DataStructures/ArrayList/arraylist.h"

/*
  función para comparar claves de tipo string
  retorna 1 si son iguales
*/
int is_equal_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}

//====================================================================================================
// FUNCIONES PARA EL MANEJO DE TECLAS Y CURSOR
//====================================================================================================

// Funcion para resetear teclas presionadas
void resetearTeclas()
{
    while (GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(VK_RETURN))
    {
        for (int i = 0x41; i <= 0x5A; i++) {
            GetAsyncKeyState(i);
        }

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

void mostrarCursor()
{
    HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursInfo;
    cursInfo.dwSize = 2;
    cursInfo.bVisible = TRUE;
    SetConsoleCursorInfo( consola, &cursInfo);
}

//====================================================================================================
// HERRAMIENTAS
//====================================================================================================

// Funcion para limpiar una linea de la consola en una posicion especifica
void limpiarLinea(int x, int y, int n)
{
    gotoxy(x, y);
 
    for(int i = 0; i < n; i++)
    {
        printf(" ");
    }
}

// Funcion para limpiar la pantalla excepto el cuadro
void limpiarPantalla()
{
    for(int i = 1; i < 24; i++)
    {
        gotoxy(2, i); printf("                                                                                                                    ");
    }
}

// Funcion para simular pausa con uso de gotoxy y getasynckeystate
void pause(int x, int y, char *mensaje)
{
    // Limpiar teclas presionadas
    resetearTeclas();

    // Mensaje de pausa
    while(!GetAsyncKeyState(VK_RETURN))
    {
        gotoxy(x, y);
        printf("%s", mensaje);
    }

    // Largo del mensaje
    int largo = strlen(mensaje);

    // Se limpia la linea anterior
    limpiarLinea(x, y, largo);
}

//====================================================================================================
// FUNCIONES DE FRONTEND - MODULARES
//====================================================================================================

//=================================
//========VENTANA PRINCIPAL========
//=================================

// Función para mostrar el cuadro
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

// Función para mostrar el dibujo del ahorcado
void mostrarAhorcado(int x, int y, int intentos)
{
    // Se muestra el ahorcado
    // gotoxy(6, 3); printf("     ___________");
    // gotoxy(6, 4); printf("     |         |");
    // gotoxy(6, 5); printf("     |         |");
    // gotoxy(6, 6); printf("     |         %c", (intentos < 6) ? 'O' : ' ');
    // gotoxy(6, 7); printf("     |        %c%c%c", (intentos < 5) ? '/' : ' ', (intentos < 4) ? '|' : ' ', (intentos < 3) ? '\\' : ' ');
    // gotoxy(6, 8); printf("     |        %c %c", (intentos < 2) ? '/' : ' ', (intentos < 1) ? '\\' : ' ');
    // gotoxy(6, 9); printf("     |");
    // gotoxy(6, 10); printf("     |");
    // gotoxy(6, 11); printf("     |");
    // gotoxy(6, 12); printf("    _|___");
    // gotoxy(6, 13); printf("");

    // Se muestra el ahorcado
    gotoxy(x, y); printf("     ___________");
    gotoxy(x, y + 1); printf("     |         |");
    gotoxy(x, y + 2); printf("     |         |");
    gotoxy(x, y + 3); printf("     |         %c", (intentos < 6) ? 'O' : ' ');
    gotoxy(x, y + 4); printf("     |        %c%c%c", (intentos < 5) ? '/' : ' ', (intentos < 4) ? '|' : ' ', (intentos < 3) ? '\\' : ' ');
    gotoxy(x, y + 5); printf("     |        %c %c", (intentos < 2) ? '/' : ' ', (intentos < 1) ? '\\' : ' ');
    gotoxy(x, y + 6); printf("     |");
    gotoxy(x, y + 7); printf("     |");
    gotoxy(x, y + 8); printf("     |");
    gotoxy(x, y + 9); printf("    _|___");
    gotoxy(x, y + 10); printf("");
}

// Función para mostrar animación de cargando
void cargando(int duracion)
{
    // Se limpia la pantalla
    limpiarPantalla();

    // Se inicializa la variable para mostrar el ahorcado
    int j = 0;

    // Se inicializa la variable para la duracion de cada mensaje
    int milisegundos = 250;

    // Se hace un bucle para mostrar el mensaje de cargando
    for(int i = 0; i < duracion; i++)
    {
        gotoxy(45, 12); printf("Cargando");
        mostrarAhorcado(15, 6, j);
        j++;
        Sleep(milisegundos);
        gotoxy(45, 12); printf("Cargando.");
        mostrarAhorcado(15, 6, j);
        j++;
        Sleep(milisegundos);
        gotoxy(45, 12); printf("Cargando..");
        mostrarAhorcado(15, 6, j);
        j++;
        Sleep(milisegundos);
        gotoxy(45, 12); printf("Cargando...");
        mostrarAhorcado(15, 6, j);
        j++;
        Sleep(milisegundos);

        // Se limpia la linea anterior
        limpiarLinea(45, 12, 11);
    }
}

// Función para mostrar el título
void mostrarTitulo(int x, int y, int opcion)
{
    // Se imprime el titulo en rojo
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);

    /***
     *   _______________________________
     *  |    _____  _    ___   _        |                           _        
     *  |   |  ___|| |  / _ \ | |       |                          | |       
     *  |   | |__  | | / /_\ \| |__    _|_   _ __   ___   __ _   __| |  ___  
     *  |   |  __| | | |  _  || '_ \  /   \ | '__| / __| / _` | / _` | / _ \ 
     *  |   | |___ | | | | | || | | || X X || |   | (__ | (_| || (_| || (_) |
     *  |   \____/ |_| \_| |_/|_| |_| \_-_/ |_|    \___| \__,_| \__,_| \___/ 
     *  |                               |                                     
     * _|_________                     /|\                                       
     *                                / | \
     *			                       / \
     *				                  /   \
     */

    if(opcion == 1)
    {
        gotoxy(x, y);     printf("   _______________________________");
        gotoxy(x, y + 1); printf("  |    _____  _    ___   _        |                           _");
        gotoxy(x, y + 2); printf("  |   |  ___|| |  / _ \\ | |       |                          | |");
        gotoxy(x, y + 3); printf("  |   | |__  | | / /_\\ \\| |__    _|_   _ __   ___   __ _   __| |  ___");
        gotoxy(x, y + 4); printf("  |   |  __| | | |  _  || '_ \\  /   \\ | '__| / __| / _` | / _` | / _ \\");
        gotoxy(x, y + 5); printf("  |   | |___ | | | | | || | | || X X || |   | (__ | (_| || (_| || (_) |");
        gotoxy(x, y + 6); printf("  |   \\____/ |_| \\_| |_/|_| |_| \\_-_/ |_|    \\___| \\__,_| \\__,_| \\___/");
        gotoxy(x, y + 7); printf("  |                               |");
        gotoxy(x, y + 8); printf(" _|_________                     /|\\");
        gotoxy(x, y + 9); printf("                                / | \\");
        gotoxy(x, y + 10); printf("			          / \\");
        gotoxy(x, y + 11); printf("				 /   \\");
    }

    /* ___          __        __   ___  ___  __   __   __ *
    * |___ |       |__| |__| |  | |__/ |    |__| |  \ |  | *
    * |___ |___    |  | |  | |__| |  \ |___ |  | |__/ |__| */

    if(opcion == 2)
    {
        gotoxy(x, y); printf(" ___          __        __   ___  ___  __   __   __");
        gotoxy(x, y + 1); printf("|___ |       |__| |__| |  | |__/ |    |__| |  \\ |  |");
        gotoxy(x, y + 2); printf("|___ |___    |  | |  | |__| |  \\ |___ |  | |__/ |__|");
    
    }

    /*  ____  __        __    _   _  _____  ____   ___    __    ____   _____ *
     * ( ___)(  )      /__\  ( )_( )(  _  )(  _ \ / __)  /__\  (  _ \ (  _  ) *
     *  )__)  )(__    /(__)\  ) _ (  )(_)(  )   /( (__  /(__)\  )(_) ) )(_)( *
     * (____)(____)  (__)(__)(_) (_)(_____)(_)\_) \___)(__)(__)(____/ (_____) */

    if(opcion == 3)
    {
        gotoxy(x, y); printf(" ____  __        __    _   _  _____  ____   ___    __    ____   _____");
        gotoxy(x, y + 1); printf("( ___)(  )      /__\\  ( )_( )(  _  )(  _ \\ / __)  /__\\  (  _ \\ (  _  )");
        gotoxy(x, y + 2); printf(" )__)  )(__    /(__)\\  ) _ (  )(_)(  )   /( (__  /(__)\\  )(_) ) )(_)( ");
        gotoxy(x, y + 3); printf("(____)(____)  (__)(__)(_) (_)(_____)(_)\\_) \\___)(__)(__)(____/ (_____)");
    }

    /***
     *      _    _              _____       _     _     _             _        _   _ _           _ 
     *     | |  | |            / ____|     | |   (_)   | |           | |      | \ | (_)         | |
     *     | |__| | __ _ ___  | (___  _   _| |__  _  __| | ___     __| | ___  |  \| |___   _____| |
     *     |  __  |/ _` / __|  \___ \| | | | '_ \| |/ _` |/ _ \   / _` |/ _ \ | . ` | \ \ / / _ \ |
     *     | |  | | (_| \__ \  ____) | |_| | |_) | | (_| | (_) | | (_| |  __/ | |\  | |\ V /  __/ |
     *     |_|  |_|\__,_|___/ |_____/ \__,_|_.__/|_|\__,_|\___/   \__,_|\___| |_| \_|_| \_/ \___|_|                                                                                          
     */

    if(opcion == 4)
    {
        gotoxy(x, y); printf("     _    _              _____       _     _     _             _        _   _ _           _");
        gotoxy(x, y + 1); printf("    | |  | |            / ____|     | |   (_)   | |           | |      | \\ | (_)         | |");
        gotoxy(x, y + 2); printf("    | |__| | __ _ ___  | (___  _   _| |__  _  __| | ___     __| | ___  |  \\| |___   _____| |");
        gotoxy(x, y + 3); printf("    |  __  |/ _` / __|  \\___ \\| | | | '_ \\| |/ _` |/ _ \\   / _` |/ _ \\ | . ` | \\ \\ / / _ \\ |");
        gotoxy(x, y + 4); printf("    | |  | | (_| \\__ \\  ____) | |_| | |_) | | (_| | (_) | | (_| |  __/ | |\\  | |\\ V /  __/ |");
        gotoxy(x, y + 5); printf("    |_|  |_|\\__,_|___/ |_____/ \\__,_|_.__/|_|\\__,_|\\___/   \\__,_|\\___| |_| \\_|_| \\_/ \\___|_|");
    }


    // Se restablece el color de la consola
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

//================================
//=======MENÚ DEL SISTEMA=========
//================================

// Función para mostrar el menú
void mostrarMenu(int x, int y, int opcionSeleccionada, int maxOpcion)
{
    if(maxOpcion == 4)
    {
        gotoxy(x, y); printf("%s JUGAR", (opcionSeleccionada == 1) ? "->" : "  ");
        gotoxy(x, y + 1); printf("%s Ver Puntuaciones", (opcionSeleccionada == 2) ? "->" : "  ");
        gotoxy(x, y + 2); printf("%s Elegir Idioma", (opcionSeleccionada == 3) ? "->" : "  ");
        gotoxy(x, y + 3); printf("%s Instrucciones", (opcionSeleccionada == 4) ? "->" : "  ");
    }

    if(maxOpcion == 2)
    {
        gotoxy(x, y); printf("%s Nueva Partida", (opcionSeleccionada == 1) ? "->" : "  ");
        gotoxy(x, y + 1); printf("%s Cargar Partida", (opcionSeleccionada == 2) ? "->" : "  ");
    }

    if(maxOpcion == 4)
    {
        gotoxy(x, y); printf("%s Continuar", (opcionSeleccionada == 1) ? "->" : "  ");
        gotoxy(x, y + 1); printf("%s Guardar y Continuar", (opcionSeleccionada == 2) ? "->" : "  ");
        gotoxy(x, y + 2); printf("%s Guardar y Salir", (opcionSeleccionada == 3) ? "->" : "  ");
        gotoxy(x, y + 3); printf("%s Salir", (opcionSeleccionada == 4) ? "->" : "  ");
    }
}

// Funcion para mostrar jugadores estilo menu
void mostrarJugadores(int x, int y, ArrayList *jugadores, int opcionSeleccionada, bool cambioOpcion)
{
    // Si cambioOpcion es true, se limpia la pantalla
    if(cambioOpcion)
    {
        // Se limpia dentro del cuadro
        for(int i = 0; i < 3; i++)
        {
            limpiarLinea(x, y + (i * 4), 85);
            limpiarLinea(x, y + (i * 4) + 1, 85);
            limpiarLinea(x, y + (i * 4) + 2, 85);
        }
    }

    // Se inicializa el contador
    int contador = 0;
    int posicion = 0;

    // Si el cursor supera el 9, entonces se debe mostrar los siguientes jugadores desde la posicion inicial
    if((opcionSeleccionada - 1) > 8)
    {
        posicion = posicion + ((opcionSeleccionada - 1) / 9) * 9;
    }

    while(posicion < get_size(jugadores))
    {
        // Se obtiene el jugador del arreglo
        Jugador *jugadorActual = get(jugadores, posicion);

        // Si contador es mayor a un multiplo de 3, se aumenta el x
        if(contador > 0 && (contador % 3) == 0)
        {
            x += 30;
            contador = 0;
        }

        // Si el cursor esta en la posicion actual, se cambia el color
        if((opcionSeleccionada - 1) == posicion)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        }

        // Se muestra el jugador actual
        gotoxy(x, y + (contador * 4)); printf("%s %s\n", ((opcionSeleccionada - 1) == posicion) ? "->" : "  ", jugadorActual->nombre);
        gotoxy(x, y + (contador * 4) + 1); printf("   - %d puntos\n", jugadorActual->puntos);
        gotoxy(x, y + (contador * 4) + 2); printf("   - Nivel %d\n", jugadorActual->nivel);

        // Se aumenta el contador
        contador++;
        posicion++;

        // Se restablece el color de la consola
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

        if(posicion % 9 == 0 || posicion >= get_size(jugadores))
        {
            break;
        }
    }
}

// Función para cambiar la opción del menú
bool cambiarOpcion(int * opcion, int maxOpcion)
{
    // Se limpia el buffer de teclado
    resetearTeclas();

    Sleep(150);
    if( GetAsyncKeyState(VK_UP) )
    {
        *opcion -= 1;

        if(*opcion < 1)
        {
            *opcion = 1;
        }
    }
    if( GetAsyncKeyState(VK_DOWN) )
    {
        *opcion += 1;

        if(*opcion > maxOpcion)
        {
            *opcion = maxOpcion;
        }
    }

    // Si maxOpcion es mayor a 4, se verifica si se priona derecha o izquierda
    if(maxOpcion >= 4)
    {
        if( GetAsyncKeyState(VK_LEFT) )
        {
            *opcion -= 3;

            if(*opcion < 1)
            {
                *opcion = 1;
            }
        }
        if( GetAsyncKeyState(VK_RIGHT) )
        {
            *opcion += 3;

            if(*opcion > maxOpcion)
            {
                *opcion = maxOpcion;
            }
        }
    }

    if( GetAsyncKeyState(VK_RETURN) )
    {
        return true;
    }
    if( GetAsyncKeyState(VK_ESCAPE) && maxOpcion == 3)
    {
        exit(0);
    }

    return false;
}

//=====================================
//========VENTANA JUGAR PARTIDA========
//=====================================

// Funcion para mostrar las letras usadas en el nivel
void mostrarLetras(int x, int y, Nivel *nivel)
{
    // Se muestra la tabla de letras usadas
    gotoxy(x, y); printf(" ___Letras usadas___");
    gotoxy(x, y + 1); printf("|                   |");
    gotoxy(x, y + 2); printf("|                   |");
    gotoxy(x, y + 3); printf("|___________________|");

    // Se obtiene el primer elemento de la lista
    char *letraActual = firstList(nivel->letrasJugadas);

    int contador = 1;

    while(letraActual != NULL)
    {
        // Se muestra la letra actual
        //    Letras usadas
        //  ___________________
        // |A-B-C-D-E-F-G-H-I-J|
        // |                   |
        // |___________________|

        if(contador == 1 || (((contador - 1) % 10) == 0))
        {
            if(contador != 1)
            {
                y++;
                contador = 1;
            }

            gotoxy(x + 1, y + 1); printf("%c", toupper(*letraActual));
        }
        else
        {
            gotoxy(x + (contador - 2) + contador, y + 1); printf("-%c", toupper(*letraActual));
        }

        // Se obtiene el siguiente elemento de la lista
        letraActual = nextList(nivel->letrasJugadas);

        // Se aumenta el contador
        contador++;
    }

}

void mostrarInformacion(int x, int y, Jugador *jugador, Nivel *nivel)
{
    // Se crea un cuadro
    cuadro(x, y, x + 29, y + 20);

    // Se imprime titulo
    gotoxy(x + 2, y + 1); printf("** INFORMACION JUGADOR **");

    // Se muestra el nombre del jugador
    gotoxy(x + 5, y + 3); printf("Jugador: %s", jugador->nombre);
    gotoxy(x + 5, y + 4); printf("===============");

    // Se muestra la tabla de Nivel
    gotoxy(x + 5, y + 5); printf("Nivel Actual: %d", jugador->nivel);
    gotoxy(x + 5, y + 6); printf("===============");
    
    // Se muestra la tabla de puntos
    gotoxy(x + 5, y + 7); printf("Puntos: %d", jugador->puntos);
    gotoxy(x + 5, y + 8); printf("===============");

    // Se agrega una linea de separacion al cuadro
    gotoxy(x + 1, y + 9); printf("___________________________");

    // Se imprime titulo
    gotoxy(x + 2, y + 11); printf("** INFORMACION NIVEL **");

    // Se muestra la tabla de Nivel
    gotoxy(x + 5, y + 13); printf("Nivel: %d", nivel->nivel);
    gotoxy(x + 5, y + 14); printf("===============");

    // Se muestra la tabla de intentos
    gotoxy(x + 5, y + 15); printf("Intentos: %d", nivel->intentosRestantes);
    gotoxy(x + 5, y + 16); printf("===============");
    
    // Se muestra la tabla de puntos
    gotoxy(x + 5, y + 17); printf("Puntos: %5d", nivel->puntosNivel);
    gotoxy(x + 5, y + 18); printf("===============");
}

void mostrarPalabra(int x, int y, Nivel *nivel)
{
    // Se obtiene el largo de la palabra actual
    int largo = strlen(nivel->palabraActual);
    
    // Se muestra la palabra actual con los guiones bajos saltando un espacion por guion
    gotoxy(x, y); printf("Palabra a adivinar:");
    for(int i = 0; nivel->palabraActual[i] != '\0'; i++)
    {
        // Se imprime debajo y al centro de la palabra a adivinar
        gotoxy(x + (10 - largo) + (i * 2), y + 2); printf("%c", toupper(nivel->palabraActual[i]));
    }
}

void procesarLetra(int x, int y, Nivel *nivel, char letra)
{
    int aciertos = 0;

    // Se recorre la palabra secreta
    for(int i = 0; i < strlen(nivel->palabraSecreta); i++)
    {
        // Se compara la letra ingresada con la letra de la palabra secreta
        if(nivel->palabraSecreta[i] == letra)
        {
            // Se agrega la letra a la palabra actual
            nivel->palabraActual[i] = letra;

            // Se aumenta el contador de aciertos
            aciertos++;
        }
    }

    // Se verifica si se ha acertado alguna letra
    if(aciertos > 0)
    {
        // Se muestra el mensaje de acierto
        gotoxy(x, y); printf("Has acertado %d letras", aciertos);

        // Se muestra el mensaje de pausa
        pause(x, y + 2, "Presione enter para continuar...");
    }
    else
    {
        // Se muestra el mensaje de error
        gotoxy(x, y); printf("La letra ingresada no se encuentra en la palabra");

        // Se muestra el mensaje de pausa
        pause(x, y + 2, "Presione enter para continuar...");

        // Se resta un intento
        nivel->intentosRestantes--;

        // Se restan 100 puntos
        nivel->puntosNivel -= 100;
    }

    // Se limpia la linea anterior
    limpiarLinea(x, y, 50);
}

// Se verifica las teclas presionadas con la funcion GetAsyncKeyState
void teclaPresionada(int x, int y, char* letra, Nivel *nivel)
{
    // Se limpia el buffer de teclado
    resetearTeclas();

    // Se inicializa la variable tecla
    bool tecla = false;

    while (!tecla)
    {
        for (int i = 0x41; i <= 0x5A; i++)
        {
            if (GetAsyncKeyState(i)) {
                *letra = i + 32; // Convertir a minúscula
                tecla = true;

                // Se imprime la letra ingresada en mayuscula
                gotoxy(x, y); printf("%c", toupper(*letra));

                // Se limpia las teclas presionadas
                resetearTeclas();

                // Se verifica si la letra ya fue ingresada
                char *letraActual = firstList(nivel->letrasJugadas);

                while(letraActual != NULL)
                {
                    if(*letraActual == *letra)
                    {
                        // Se muestra el mensaje de error
                        gotoxy(50, 20); printf("La letra ingresada ya fue utilizada");
                        
                        ocultarCursor();

                        // Se muestra el mensaje de pausa
                        pause(50, 22, "Presione enter para continuar...");

                        // Se limpia la linea anterior
                        limpiarLinea(50, 20, 50);

                        // Se limpia la letra ingresada
                        limpiarLinea(x, y, 1);

                        mostrarCursor();

                        // Se cambia el valor de la variable tecla
                        tecla = false;

                        break;
                    }

                    // Se obtiene el siguiente elemento de la lista
                    letraActual = nextList(nivel->letrasJugadas);
                }

                if(tecla == false)
                {
                    // Se limpia el buffer de teclado
                    resetearTeclas();
                    break;
                }

                // Se limpia el buffer de teclado
                resetearTeclas();

                while(!GetAsyncKeyState(VK_RETURN) && !GetAsyncKeyState(VK_BACK));
                {
                    if(GetAsyncKeyState(VK_BACK))
                    {
                        // Se limpia la linea anterior
                        limpiarLinea(x, y, 1);

                        // Se limpia la variable letra
                        *letra = '\0';

                        // Se cambia el valor de la variable tecla
                        tecla = false;
                    }
                }

                break;
            }
        }
    }
}

//=====================================
//========VENTANA INSTRUCCIONES========
//=====================================

void mostrarInstrucciones(int x, int y)
{
    gotoxy(x, y); printf("Instrucciones:");
    gotoxy(x, y+2); printf("1. Adivina la palabra oculta en el menor numero de intentos posible.");
    gotoxy(x, y+3); printf("2. Cada nivel tiene una palabra de longitud especifica, aumentando en un caracter por nivel.");
    gotoxy(x, y+4); printf("3. Necesitas alcanzar 1000 puntos por nivel para avanzar.");
    gotoxy(x, y+5); printf("4. Cada intento fallido disminuye tu puntaje base.");
    gotoxy(x, y+6); printf("5. Selecciona la opcion correspondiente para adivinar una letra de la palabra oculta.");
    gotoxy(x, y+7); printf("6. Si adivinas correctamente, se revelaran las apariciones de la letra en la palabra.");
    gotoxy(x, y+8); printf("7. Completa el nivel antes de agotar los intentos para obtener puntos adicionales; de lo contrario,");
    gotoxy(x, y+9); printf("   no ganas puntos y pierdes el nivel.");

}



// Funcion para mostrar el menu de nivel
void menuNivel(Jugador *jugador)
{
    // Se crea la variable para guardar la opcion seleccionada
    int opcionSeleccionada = 1;

    // Se limpia la pantalla
    limpiarPantalla();

    // Se muestra el titulo
    mostrarTitulo(12, 3, 4);

    // Se muestra titulo menu
    gotoxy(40, 12); printf("Que desea hacer?");

    while(true)
    {
        while(!cambiarOpcion(&opcionSeleccionada, 4))
        {
            // Se muestra el menu
            mostrarMenu(40, 14, opcionSeleccionada, 4);
        }

        switch(opcionSeleccionada)
        {
            case 1:
                // Continuar
                cargando(2);

                break;
            case 2:
                // Guardar y continuar

                // Se llama a la funcion para guardar partida
                guardarPartida(jugador, 40, 20);

                // Se muestra el mensaje de pausa
                pause(40, 22, "Presione enter para continuar...");

                // Se llama a cargando
                cargando(2);

                break;
            case 3:
                // Guardar y salir

                // Se llama a la funcion para guardar partida
                guardarPartida(jugador, 40, 20);

                // Se muestra el mensaje de pausa
                pause(40, 22, "Presione enter para salir...");

                // Se sale de la aplicacion
                exit(0);

                break;
            case 4:
                // Salir

                // Se muestra el mensaje de pausa
                pause(40, 22, "Presione enter para salir...");

                // Se sale de la aplicacion
                exit(0);

                break;
        }
        break;
    }
}

//====================================================================================================
// FUNCIONES DE FRONTEND - PRINCIPALES
//====================================================================================================

// Prototipado de funciones
void menu(Jugador *jugador);
void subMenuJugar(Jugador *jugador);
void nuevaPartida(Jugador *jugador);
void cargarPartidaFE(Jugador *jugador);
void jugar(Jugador *jugador);
void instrucciones();

//================================
//========MENU PRINCIPAL==========
//================================

// Función para mostrar el menú
void menu(Jugador *jugador)
{
    // Se inicia un booleano para inicio de juego
    bool inicioJuego = true;

    // Se inicializa el mapa de palabras jugadas
    jugador->palabrasJugadas = createMap(is_equal_string);

    while(true)
    {
        int opcionSeleccionada = 1;

        system("cls"); // Limpiar la pantalla
        cuadro(1, 0, 119, 25); // Se dibuja el cuadro

        mostrarTitulo(25, 4, 1); // Se muestra el titulo

        if(inicioJuego)
        {
            // Se cambia el color de la consola a verde
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);

            // Se muestra el mensaje de pausa
            pause(35, 18, "Presione ENTER para iniciar juego...");

            inicioJuego = false;

            // Se restablece el color de la consola
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        }

        while(!cambiarOpcion(&opcionSeleccionada, 4))
        {
            mostrarMenu(40, 16, opcionSeleccionada, 4);
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
            case 4:
                // Se llama a la funcion instrucciones
                instrucciones();

                break;
        }
    }
}

//===================================
//========SUBMENU JUGAR =============
//===================================

// Función para mostrar el submenú de jugar
void subMenuJugar(Jugador *jugador)
{
    int opcionSeleccionada = 1;

    // Se limpia la pantalla del menú
    limpiarLinea(40, 16, 20);
    limpiarLinea(40, 17, 20);
    limpiarLinea(40, 18, 20);
    limpiarLinea(40, 19, 20);

    while(true)
    {
        while(!cambiarOpcion(&opcionSeleccionada, 2))
        {
            mostrarMenu(40, 16, opcionSeleccionada, 2);
        }

        switch(opcionSeleccionada)
        {
            case 1:
                nuevaPartida(jugador);               

                break;
            case 2:
                cargarPartidaFE(jugador);

                break;
        }

        // Se limpia las lineas
        limpiarLinea(30, 20, 35);
        limpiarLinea(30, 22, 35);

        break;
    }    
}

// Funcion para nuevo juego
void nuevaPartida(Jugador *jugador)
{
    // Se limpia la pantalla del menú
    limpiarLinea(40, 16, 20);
    limpiarLinea(40, 17, 20);

    // Se crea una variable para guardar el nombre del jugador
    char nombre[50];

    mostrarCursor();

    // Se obtiene el nombre del jugador
    gotoxy(40, 16);

    // Linea para que el cursor se mantenga en la misma linea
    system("timeout /t 0 /nobreak >nul");

    // Se obtiene el nombre del jugador
    printf("Ingrese su nombre: ");
    scanf("%s", nombre);

    while(getchar() != '\n'); // Limpiar buffer

    ocultarCursor();

    // Se guarda el nombre del jugador
    strcpy(jugador->nombre, nombre);

    // Se limpia la linea anterior
    limpiarLinea(40, 16, 30);

    // Se inicializa el nivel y los puntos del jugador
    jugador->nivel = 1;
    jugador->puntos = 0;

    // Se cambia el color de la consola a amarillo
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);

    // Se muestra el mensaje de bienvenida
    gotoxy(35, 17); printf("BIENVENIDO %s!!!!!!!", jugador->nombre);

    // Se muestra el mensaje de pausa
    pause(35, 18, "Presione enter para comenzar...");

    // Se restaura el color de la consola
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

    cargando(2);

    jugar(jugador);
}

void cargarPartidaFE(Jugador *jugador)
{
    // Se muestra cargando
    cargando(2);
    
    // Se limpia la pantalla
    limpiarPantalla();

    // Se muestra el titulo
    mostrarTitulo(35, 1, 2);

    // Se imprime Seleccione una partida guardada
    gotoxy(45, 6); printf("Seleccione una partida guardada:");

    // Se crea un cuadro para mostrar las partidas guardadas
    cuadro(15, 7, 105, 22);

    // Se crea una arreglo para guardar los jugadores
    ArrayList *jugadores = createArrayList();

    // Se llama a la funcion para obtener los jugadores
    obtenerJugadores(jugadores);

    // Se crea una variable para guardar la opcion seleccionada
    int opcionSeleccionada = 1;

    while(true)
    {
        // Se crea un booleano para saber si se la opcion seleccionada supero los 9
        bool cambioOpcion = false;

        // Se crea un entero para saber en que rango se encuentra la opcion seleccionada
        int rango = (opcionSeleccionada - 1) / 9;

        while(!cambiarOpcion(&opcionSeleccionada, get_size(jugadores)))
        {
            // Se comprueba si la opcion seleccionada cambio de rango
            if(rango != ((opcionSeleccionada - 1) / 9))
            {
                // Se cambia el valor de la variable cambioOpcion
                cambioOpcion = true;

                // Se cambia el valor de la variable rango
                rango = (opcionSeleccionada - 1) / 9;
            }

            // Se muestran los jugadores en el cuadro
            mostrarJugadores(19, 9, jugadores, opcionSeleccionada, cambioOpcion);

            // Se cambia el valor de la variable cambioOpcion
            cambioOpcion = false;
        }

        break;
    }

    // Se obtiene el jugador seleccionado
    Jugador *jugadorSeleccionado = get(jugadores, opcionSeleccionada - 1);

    // Se copia el jugador seleccionado al jugador actual
    strcpy(jugador->nombre, jugadorSeleccionado->nombre);
    jugador->nivel = jugadorSeleccionado->nivel;
    jugador->puntos = jugadorSeleccionado->puntos;

    // Se hace una pause
    pause(45, 22, "Presione enter para continuar...");

    // Se muestra cargando
    cargando(2);

    // Se llama a la funcion jugar
    jugar(jugador);
}

// Funcion Jugar
void jugar(Jugador *jugador)
{
    //================================================================
    //================= BACKEND JUGAR ================================
    //================================================================

    // Se crea una estructura para guardar el nivel
    Nivel *nivel = (Nivel *)malloc(sizeof(Nivel));

    // Se inicializa el nivel
    nivel->nivel = jugador->nivel;
    nivel->letrasJugadas = createList();
    nivel->intentosRestantes = 6;

    // Se inicializa los puntos del nivel segun el nivel del jugador
    nivel->puntosNivel = 600 + (200 * (nivel->nivel - 1));

    // Se llama a la funcion para agregar una palabra aleatoria
    agregarPalabraAleatoria(jugador, nivel);

    // Se llena de guiones bajos la palabra actual
    for(int i = 0; i < strlen(nivel->palabraSecreta); i++)
    {
        nivel->palabraActual[i] = '_';
    }
    nivel->palabraActual[strlen(nivel->palabraSecreta)] = '\0'; // Se agrega el caracter nulo

    // Creacion de variables
    bool ganar = false; // Variable para saber si se ha ganado el juego
    char letra; // Variable para guardar la letra ingresada
    bool limpiarLetra = false; // Variable para saber si se debe limpiar la letra ingresada
    bool subirNivel = false; // Variable para saber si se debe subir de nivel

    // Se limpia la pantalla
    limpiarPantalla();

    // Se hace el bucle para mostrar el juego
    while(nivel->intentosRestantes > 0 && !ganar)
    {
        //================================================================
        //================= FRONTEND JUGAR ===============================
        //================================================================

        // Se limpia la letra ingresada si es que se ha ingresado una
        if(limpiarLetra)
        {
            // Se limpia la letra ingresada
            limpiarLinea(85, 17, 1);
        }

        // Se muestra el titulo
        mostrarTitulo(50, 1, 2);

        // Se muestra la informacion del juego actual
        mostrarInformacion(8, 3, jugador, nivel);

        // Se muestra el ahorcado
        mostrarAhorcado(45, 6, nivel->intentosRestantes);

        // Se muestra las letras usadas
        mostrarLetras(85, 6, nivel);

        // Se muestra la palabra actual con los guiones bajos saltando un espacion por guion
        mostrarPalabra(65, 12, nivel);

        // Se pregunta por la letra
        gotoxy(65, 17); printf("Ingrese una letra:  ");

        mostrarCursor(); // Se muestra el cursor

        // Se llama a la funcion que verifica que letra se ha ingresado
        teclaPresionada(85, 17, &letra, nivel);

        ocultarCursor(); // Se oculta el cursor

        //================================================================
        //================= BACKEND JUGAR ================================
        //================================================================

        // Se copia el puntero a una nueva direccion de memoria
        char *letraIngresada = (char *)malloc(sizeof(char));
        *letraIngresada = letra;

        // Se guarda la letra ingresada en la lista de letras jugadas
        pushBack(nivel->letrasJugadas, letraIngresada);

        // Se cambia el valor de la variable limpiarLetra
        limpiarLetra = true;

        // Se llama a funcion para validar la letra ingresada
        procesarLetra(50, 20, nivel, letra);

        // Se verifica si se ha ganado el juego
        if(strcmp(nivel->palabraSecreta, nivel->palabraActual) == 0)
        {
            // Se cambia el valor de la variable ganar
            ganar = true;
        }
    }

    // Se verifica si se ha ganado el juego
    if(ganar)
    {
        // Se muestra la ultima letra ingresada
        mostrarPalabra(65, 12, nivel);

        // Se aumenta los puntos del jugador
        jugador->puntos += nivel->puntosNivel;

        // Se muestra el mensaje de felicitaciones
        gotoxy(50, 20); printf("FELICITACIONES HAS COMPLETADO LA PALABRA!!!!!!!");

        // Se muestra el mensaje de pausa
        pause(50, 22, "Presione enter para continuar...");

        // Se verifica la cantidad de puntos del jugador para subir de nivel
        if(jugador->puntos >= 1000 * jugador->nivel)
        {
            // Se aumenta el nivel del jugador
            jugador->nivel++;

            // Se limpia la linea anterior
            limpiarLinea(50, 20, 50);

            // Se cambia el valor de la variable subirNivel
            subirNivel = true;
        }
    }
    else
    {
        // Se muestra el mensaje de perdiste
        gotoxy(50, 20); printf("PERDISTE!!!!!!!");

        // Se muestra la palabra secreta
        gotoxy(50, 21); printf("La palabra secreta era: %s", nivel->palabraSecreta);

        // Se muestra el mensaje de pausa
        pause(50, 22, "Presione enter para continuar...");

        // Se sale de la funcion
        return;
    }

    // Se libera la memoria de la estructura nivel
    free(nivel);

    // Se llama a cargar
    cargando(2);

    // Se verifica si se debe subir de nivel
    if(subirNivel)
    {
        // Se llama a la funcion si se subio de nivel
        menuNivel(jugador);
    }

    // Se llama a la funcion jugar
    jugar(jugador);
}

//  Funcion instrucciones
void instrucciones()
{
    // Se limpia la pantalla
    limpiarPantalla();

    // Se muestra el titulo
    mostrarTitulo(30, 1, 2);

    // Se muestra el mensaje de instrucciones
    mostrarInstrucciones(7, 6);

    // Se llama a la función pause
    pause(30, 23, "Presione enter para continuar...");

    // Se llama a cargar
    cargando(2);
}