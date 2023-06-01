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
        gotoxy(2, i); printf("                                                                                                    ");
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
        gotoxy(30, 12); printf("Cargando");
        mostrarAhorcado(5, 6, j);
        j++;
        Sleep(milisegundos);
        gotoxy(30, 12); printf("Cargando.");
        mostrarAhorcado(5, 6, j);
        j++;
        Sleep(milisegundos);
        gotoxy(30, 12); printf("Cargando..");
        mostrarAhorcado(5, 6, j);
        j++;
        Sleep(milisegundos);
        gotoxy(30, 12); printf("Cargando...");
        mostrarAhorcado(5, 6, j);
        j++;
        Sleep(milisegundos);

        // Se limpia la linea anterior
        limpiarLinea(30, 12, 11);
    }
}

// Función para mostrar el título
void mostrarTitulo(int x, int y, int opcion)
{
    // Se imprime el titulo en rojo
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);

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
        gotoxy(x, y + 3); printf("%s Intrucciones", (opcionSeleccionada == 4) ? "->" : "  ");
    }

    if(maxOpcion == 2)
    {
        gotoxy(x, y); printf("%s Nueva Partida", (opcionSeleccionada == 1) ? "->" : "  ");
        gotoxy(x, y + 1); printf("%s Cargar Partida", (opcionSeleccionada == 2) ? "->" : "  ");
    }
}

// Función para cambiar la opción del menú
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
    if( GetAsyncKeyState(VK_ESCAPE) && maxOpcion == 4){
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

void mostrarNivel(int x,  int y, Nivel *nivel)
{    
    gotoxy(x, y); printf("Nivel Actual: %d", nivel->nivel);
    gotoxy(x, y + 1); printf("===============");

}

void mostrarPuntos(int x, int y, Jugador *jugador)
{
    gotoxy(x, y); printf("Puntos: %d", jugador->puntos);
    gotoxy(x, y + 1); printf("===============");
}

void procesarLetra(Nivel *nivel, char letra)
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
        gotoxy(30, 20); printf("Has acertado %d letras", aciertos);

        // Se muestra el mensaje de pausa
        pause(30, 22, "Presione enter para continuar...");
    }
    else
    {
        // Se muestra el mensaje de error
        gotoxy(30, 20); printf("La letra ingresada no se encuentra en la palabra");

        // Se muestra el mensaje de pausa
        pause(30, 22, "Presione enter para continuar...");

        // Se resta un intento
        nivel->intentosRestantes--;
    }

    // Se limpia la linea anterior
    limpiarLinea(30, 20, 50);
}

// Se verifica las teclas presionadas con la funcion GetAsyncKeyState
void teclaPresionada(char* letra)
{
    bool tecla = false;

    while (!tecla)
    {
        for (int i = 0x41; i <= 0x5A; i++) {
            if (GetAsyncKeyState(i)) {
                *letra = i + 32; // Convertir a minúscula
                tecla = true;

                // Se imprime la letra ingresada en mayuscula
                gotoxy(49, 14); printf("%c", toupper(*letra));

                while(!GetAsyncKeyState(VK_RETURN) && !GetAsyncKeyState(VK_BACK));
                {
                    if(GetAsyncKeyState(VK_BACK))
                    {
                        // Se limpia la linea anterior
                        limpiarLinea(49, 14, 1);

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

//====================================================================================================
// FUNCIONES DE FRONTEND - PRINCIPALES
//====================================================================================================

// Prototipado de funciones
void menu(Jugador *jugador);
void subMenuJugar(Jugador *jugador);
void nuevoJuego(Jugador *jugador);
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

    while(true)
    {
        int opcionSeleccionada = 1;

        system("cls"); // Limpiar la pantalla
        cuadro(1, 0, 119, 25); // Se dibuja el cuadro

        mostrarTitulo(25, 4, 1); // Se muestra el titulo

        if(inicioJuego)
        {
            // Se cambia el color de la consola a azul
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);

            // Se muestra el mensaje de pausa
            pause(35, 18, "Presione ENTER para iniciar juego...");

            inicioJuego = false;

            // Se restablece el color de la consola
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        }

        // Resetear teclas presionadas
        resetearTeclas();

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
                // Se llama a la funcion para leer las instrucciones del juego
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
        // Resetear teclas presionadas
        resetearTeclas();

        while(!cambiarOpcion(&opcionSeleccionada, 2))
        {
            mostrarMenu(40, 16, opcionSeleccionada, 2);
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
                pause(30, 22, "Presione enter para continuar...");

                break;
        }

        // Se limpia las lineas
        limpiarLinea(30, 20, 35);
        limpiarLinea(30, 22, 35);

        break;
    }    
}

// Funcion para nuevo juego
void nuevoJuego(Jugador *jugador)
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


// Funcion Jugar
void jugar(Jugador *jugador)
{
    // Se crea una estructura para guardar el nivel
    Nivel *nivel = (Nivel *)malloc(sizeof(Nivel));

    // Se crea una variable para contar las palabras adivinadas en el nivel
    int contadorPalabras = 0;

    // Se inicia el bucle de adivinanza de palabras
    while (contadorPalabras < 5) {
        // Se inicializa el nivel
        nivel->nivel = jugador->nivel;
        nivel->letrasJugadas = createList();
        nivel->intentosRestantes = 6;

        // Se llama a la funcion para agregar una palabra aleatoria
        agregarPalabraAleatoria(jugador, nivel);

        // Se llena de guiones bajos la palabra actual
        for (int i = 0; i < strlen(nivel->palabraSecreta); i++)
        {
            nivel->palabraActual[i] = '_';
        }

        // Se agrega el caracter nulo al final de la palabra actual
        nivel->palabraActual[strlen(nivel->palabraSecreta)] = '\0';

        // Se crea un booleano para saber si se ha ganado el juego
        bool ganar = false;

        // Se crea una variable para guardar la letra ingresada
        char letra;

        // Se limpia la pantalla
        limpiarPantalla();

        // Se crea un booleano para saber cuando limpiar la letra ingresada
        bool limpiarLetra = false;

        // Se hace el bucle para mostrar el juego
        while (nivel->intentosRestantes > 0 && !ganar)
        {
            // Se reinician las teclas presionadas
            resetearTeclas();

            // Se limpia la pantalla
            if (limpiarLetra)
            {
                // Se limpia la linea anterior
                limpiarLinea(49, 14, 1);
            }

            // Limpiar teclas presionadas
            resetearTeclas();

            mostrarTitulo(25, 1, 2);

            // Se muestra el ahorcado
            mostrarAhorcado(5, 6, nivel->intentosRestantes);

            // Se muestra el nivel
            mostrarNivel(30, 7, nivel);

            // Se muestra las letras usadas
            mostrarLetras(60, 7, nivel);

            // Se muestra la palabra actual con los guiones bajos saltando un espacio por guion
            gotoxy(30, 11); printf("Palabra: ");
            for (int i = 0; nivel->palabraActual[i] != '\0'; i++)
            {
                // Se muestra la palabra en mayuscula
                printf("%c ", toupper(nivel->palabraActual[i]));
            }

            // Se pregunta por la letra
            gotoxy(30, 14); printf("Ingrese una letra: ");

            mostrarCursor();

            // Se llama a la funcion que verifica qué letra se ha ingresado
            teclaPresionada(&letra);

            ocultarCursor();

            // Se copia el puntero a una nueva direccion de memoria
            char *letraIngresada = (char *)malloc(sizeof(char));
            *letraIngresada = letra;

            // Se guarda la letra ingresada en la lista de letras jugadas
            pushBack(nivel->letrasJugadas, letraIngresada);

            // Se cambia el valor de la variable limpiarLetra
            limpiarLetra = true;

            // Se llama a la función para validar la letra ingresada
            procesarLetra(nivel, letra);

            // Se verifica si se ha ganado el juego
            if (strcmp(nivel->palabraSecreta, nivel->palabraActual) == 0)
            {
                // Se cambia el valor de la variable ganar
                ganar = true;
            }
        }

        // Se verifica si se ha ganado el juego
        if (ganar)
        {
            // Se incrementa el contador de palabras adivinadas
            contadorPalabras++;

            // Se aumenta los puntos del jugador
            jugador->puntos += 100;

            // Se muestra el mensaje de felicitaciones
            gotoxy(30, 20); printf("FELICITACIONES, HAS GANADO UNA PALABRA!!!!!!!");

            // Se muestra el mensaje de pausa
            pause(30, 22, "Presione enter para continuar...");

            // Si se adivinaron 5 palabras del mismo largo, se aumenta el nivel
            if (contadorPalabras == 5)
            {
                // Se aumenta el nivel del jugador
                jugador->nivel++;

                // Se reinicia el contador de palabras adivinadas
                contadorPalabras = 0;

                // Se muestra el mensaje de nivel ascendido
                gotoxy(30, 20); printf("¡Pasaste al siguiente nivel! Nivel %d", jugador->nivel);

                // Se muestra el mensaje de pausa
                pause(30, 22, "Presione enter para continuar...");
            }
        }
        else
        {
            // Se muestra el mensaje de perdiste
            gotoxy(30, 20); printf("PERDISTE!!!!!!!");

            // Se muestra el mensaje de pausa
            pause(30, 22, "Presione enter para continuar...");

            // Se sale del juego
            exit(0);
        }

    }

    // Se libera la memoria de la estructura nivel
    free(nivel);

    // Se llama a cargar
    cargando(2);

    // Se llama a la función jugar
    jugar(jugador);
}

void mostrarInstrucciones(int x, int y)
{
    /*
    gotoxy(30, 10); printf("Instrucciones:");
    gotoxy(30, 12); printf("1. El juego consiste en adivinar palabras.");
    gotoxy(30, 13); printf("2. Cada palabra adivinada suma 100 puntos.");
    gotoxy(30, 14); printf("3. Si adivinas 5 palabras del mismo largo, subes de nivel.");
    gotoxy(30, 15); printf("4. Si fallas 6 veces, pierdes el juego.");
    gotoxy(30, 16); printf("5. Si pierdes, se acaba el juego.");
    gotoxy(30, 17); printf("6. Si ganas, se acaba el juego.");
    gotoxy(30, 18); printf("7. Si quieres salir del juego, presiona ESC.");
    

   Adivina la palabra oculta en el menor número de intentos posible.

    Cada nivel tiene una palabra de longitud específica, aumentando en un carácter por nivel.

    Necesitas alcanzar 1000 puntos por nivel para avanzar.

    Cada intento fallido disminuye tu puntaje base.

    Selecciona la opción correspondiente para adivinar una letra de la palabra oculta.

    Si adivinas correctamente, se revelarán las apariciones de la letra en la palabra.

    Completa el nivel antes de agotar los intentos para obtener puntos adicionales; de lo contrario, no ganas puntos y pierdes el nivel.
    */

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