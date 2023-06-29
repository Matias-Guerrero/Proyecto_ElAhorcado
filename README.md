# Proyecto_ElAhorcado
 Proyecto de Estructura de Datos, Ingeniería Civil Informática

---

Juego el ahorcado con Estructuras de datos y TDAs.
======

**Preparacion y configuracion del Repositorio**

*   Usamos la aplicación `GitHub Desktop` para crear y actualizar nuestro repositorio local, para evitar usar lo comandos `git fetch` y `git pull`, ya que estos estan integrados en la app.
*   Creamos un `repositorio remoto` en GitHub, el link es el siguiente: 
*   Utilizamos Visual Studio Code para que cada uno de los integrantes clonara el repositorio en sus computadores.
*   Para subir cada commit usamos los siguiente comandos en la terminal git bash, como: `git status`, `git add .`, `git commit -m "[Message]"` y `git push`.
*   Para compilar la aplicacion se creo un script en bash llamado `compiler.sh`, el cual compila el codigo en c y crea un archivo ejecutable `.exe` con el nombre que uno ingrese.
*   Para ejecutar la aplicacion se puede hacer el llamado del ejecutable desde la terminal con el comando `./[NombreEjecutable].exe` o simplemente ejecutar el archivo `.exe` desde el administrador de archivos.

---

Estructuras de datos y TDAs implementadas
---

En esta aplicación implementamos las siguientes estructuras de datos y TDAs:

* TDA Mapa:

  ````c
  struct Node {
    void * key;
    /*! Puntero al dato */
    void * data;

    /*! Puntero al siguiente nodo */
    Node * next;

    /*! Puntero al anterior nodo */
    Node * prev;
  };
 
  struct Map {
      /*! Puntero al incio (cabeza) de la lista */
      Node * head;
  
      /*! Puntero al final (cola) de la lista */
      Node * tail;
  
      /*! Punteor para poder recorrer la lista */
      Node * current;
  
      int (*is_equal)(void* key1, void* key2);
      int (*lower_than)(void* key1, void* key2);
   };
  ````

* TDA lista
  
  ````c
  struct Node {
      const void * data;
      Node * next;
      Node * prev;
  };

  struct List {
      Node * head;
      Node * tail;
      Node * current;
  };
  ````

* Estructura de datos Arbol binario:
  
  ````c
    struct TreeNode {
        Pair* pair;
        TreeNode * left;
        TreeNode * right;
        TreeNode * parent;
    };
  
    struct TreeMap {
        TreeNode * root;
        TreeNode * current;
        int (*lower_than) (void* key1, void* key2);
    };
    ````
*Estructura de datos ArrayList:

````c
 typedef struct ArrayList {
    void **data;
    int capacity;
    int size;
} ArrayList;
````

  
Structs creadas
----

Se nos pidio realizar un proyecto final, en donde elegimos el juego del ahorcado. En donde creamos una aplicación interactiva que ofrece una experiencia personalizada y desafiante a través de niveles progresivos. Incluimos un sistema de puntuaciones para fomentar la competencia entre los jugadores y la opción de guardar y cargar partidas. La aplicación se ejecuta en la terminal, es compatible con diversos dispositivos y tiene una interfaz intuitiva.

Para mantener ordenada nuestro proyecto utilizamos `subcarpetas`.

Para esto definimos la siguiente struct en c:

* Palabra

  ````c
  typedef struct {
      char palabra[50];
      char pista[50];
      int nivel;
  } Palabra;
  ````
  
* Nivel

  ````c
  typedef struct {
    char palabraSecreta[50];
    char palabraActual[50];
    char pista[50];
    int nivel;
    int puntosNivel;
    int intentosRestantes;
    List *letrasJugadas;
  } Nivel;
  ````
  
* Jugador

  ````c
  typedef struct {
    char nombre[50];
    int puntos;
    int nivel;
    int idioma;
    Map *palabrasJugadas;
  } Jugador;
  ````

---
El programa del juego del Ahorcado comienza con la función `main()`, que crea un objeto jugador y lo inicializa. A continuación, se crea un árbol binario de búsqueda llamado `arbol_puntajes` utilizando la estructura `TreeMap`. Este árbol se utiliza para almacenar y organizar los puntajes de los jugadores.

Después de crear el árbol de puntajes, se procede a leer los puntajes existentes desde un archivo y cargarlos en el árbol utilizando la función `leerPuntajes()`. Esto permite mantener un registro de los puntajes anteriores y compararlos con los nuevos puntajes obtenidos por los jugadores.

A continuación, se configura el tamaño de la pantalla y se oculta el cursor para proporcionar una experiencia de juego más agradable. Luego, se llama a la función `menu()`, que muestra un menú interactivo donde los jugadores pueden seleccionar diferentes opciones y jugar al juego del Ahorcado.

Una vez que el jugador ha terminado de jugar, se exportan los nuevos puntajes al archivo utilizando la función `exportarPuntajes()`. Esto asegura que los puntajes actualizados se guarden para futuras sesiones de juego.

Finalmente, el programa devuelve 0 para indicar que se ha ejecutado correctamente. En resumen, el `main()` del juego del Ahorcado gestiona la configuración inicial, el registro de puntajes, la interfaz de usuario y el flujo general del juego.

Funciones Implementadas
----
- **Nueva Partida :** `void nuevaPartida(Jugador *jugador, TreeMap* arbol_puntajes)`.
  
  La función `nuevaPartida()` se encarga de iniciar un nuevo juego en el programa del juego del Ahorcado. Recibe dos argumentos: un puntero a la estructura Jugador y un   puntero al árbol binario de búsqueda de puntajes `arbol_puntajes`.

  La función comienza por limpiar la pantalla del menú y crear una variable llamada `nombre` para almacenar el nombre del jugador. Luego, se muestra el cursor y se solicita al jugador que ingrese su nombre utilizando la función `scanf()`.

  Después de leer el nombre, se oculta el cursor y se guarda el nombre ingresado en el campo `nombre` de la estructura Jugador. A continuación, se limpia la línea anterior y se inicializan el nivel y los puntos del jugador.

  Luego, se cambia el color de la consola a amarillo para mostrar un mensaje de bienvenida en función del idioma seleccionado por el jugador. Este mensaje se muestra utilizando la función `printf()` y se pasa el nombre del jugador como argumento.

  Después de mostrar el mensaje de bienvenida, se muestra un mensaje de pausa utilizando la función `pause()`. Esta función muestra un mensaje en una posición específica de la pantalla y espera a que el jugador presione la tecla Enter para continuar.

  Una vez que el jugador ha presionado Enter, se restaura el color de la consola y se llama a la función `cargando()` para mostrar una animación de carga durante 2 segundos.

  Finalmente, se llama a la función `jugar()` para comenzar el juego del Ahorcado, pasando como argumentos el puntero al jugador y el puntero al árbol de puntajes.

- **Cargar Partida :** `void cargarPartidaFE(Jugador *jugador, TreeMap* arbol_puntajes)`.
  
   La función `cargarPartidaFE()` se encarga de cargar una partida guardada en el programa del juego del Ahorcado. Recibe dos argumentos: un puntero a la estructura `Jugador` y un puntero al árbol binario de búsqueda de puntajes (`arbol_puntajes`).

   La función comienza mostrando un mensaje de carga utilizando la función `cargando()`. Luego, se limpia la pantalla y se muestra el título del juego utilizando la función `mostrarTitulo()`. A continuación, se imprime un mensaje en función del idioma seleccionado por el jugador.

   Después de imprimir el mensaje, se crea un cuadro en la pantalla para mostrar las partidas guardadas utilizando la función `cuadro()`. Luego, se crea un ArrayList llamado `jugadores` para guardar los jugadores y se llama a la función `obtenerJugadores()` para obtener los jugadores guardados.

   A continuación, se crea una variable llamada `opcionSeleccionada` para almacenar la opción seleccionada por el jugador. Se inicia un bucle while que se ejecuta hasta que el jugador seleccione una opción válida. Dentro del bucle, se verifica si la opción seleccionada cambió de rango y se muestra la lista de jugadores en el cuadro utilizando la función `mostrarJugadores()`. Esto se repite hasta que el jugador seleccione una opción válida.

   Después de salir del bucle, se obtiene el jugador seleccionado utilizando la función `get()` y se guarda en la variable `jugadorSeleccionado`. Luego, se copia la información del jugador seleccionado al jugador actual, actualizando el nombre, el nivel y los puntos.

   A continuación, se muestra un mensaje de pausa utilizando la función `pause()`, que espera a que el jugador presione la tecla Enter para continuar. Después de la pausa, se muestra nuevamente el mensaje de carga y se llama a la función `jugar()` para iniciar el juego con el jugador actual y el árbol de puntajes.


- **Jugar :** `void jugar(Jugador *jugador, TreeMap* arbol_puntajes)`.
  
   La función `jugar()` se encarga de iniciar el juego del Ahorcado. Recibe dos argumentos: un puntero a la estructura `Jugador` y un puntero al árbol binario de búsqueda de puntajes (`arbol_puntajes`).

   La función comienza verificando el idioma seleccionado por el jugador. Luego, se realiza el backend del juego del Ahorcado.

   En el backend, se crea una estructura `Nivel` para almacenar los datos del nivel actual. Se inicializan los valores del nivel, incluyendo el nivel actual del jugador, una lista para almacenar las letras jugadas y el número de intentos restantes. También se asigna el puntaje correspondiente al nivel.

   A continuación, se llama a la función `agregarPalabraAleatoria()` para seleccionar una palabra aleatoria y asignarla como la palabra secreta del nivel. Se llena la palabra actual con guiones bajos para representar las letras no adivinadas.

   Se crean variables para controlar el estado del juego, como la variable `ganar` para saber si se ha ganado el juego, la variable `letra` para almacenar la letra ingresada por el jugador, la variable `limpiarLetra` para determinar si se debe limpiar la letra ingresada y la variable `subirNivel` para saber si se debe subir de nivel.

   En el frontend del juego, se muestra la interfaz gráfica del juego, incluyendo el título, la información del juego actual, el ahorcado, las letras usadas y la palabra actual. Se solicita al jugador que ingrese una letra y se llama a la función `teclaPresionada()` para obtener la letra ingresada y validarla.

  En el backend, se guarda la letra ingresada en la lista de letras jugadas y se cambia el valor de `limpiarLetra` a true para limpiar la letra ingresada en la próxima iteración del bucle. Se llama a la función `procesarLetra()` para procesar la letra ingresada y actualizar la palabra actual.

  Se verifica si se ha ganado el juego comparando la palabra secreta con la palabra actual. Si se ha ganado, se muestra un mensaje de felicitaciones, se aumentan los puntos del jugador y se verifica si se debe subir de nivel. En caso de perder el juego, se muestra un mensaje de derrota y se muestra la palabra secreta.

  Se libera la memoria asignada a la estructura `nivel` y se llama a la función `cargando()` para mostrar un mensaje de carga. Si se debe subir de nivel, se llama a la función `menuNivel()` para mostrar el menú de selección de nivel. Luego, se llama nuevamente a la función `jugar()` para iniciar un nuevo juego.


- **Idioma :** `void idioma(Jugador *jugador)`.
  
  La función `idioma()` se encarga de permitir al jugador seleccionar el idioma en el que desea jugar. Recibe como argumento un puntero a la estructura `Jugador`.

  La función comienza almacenando el idioma original del jugador en una variable llamada `idiomaOriginal`.

  Luego, se crea una variable `opcionSeleccionada` para almacenar la opción seleccionada por el jugador. Se limpia la pantalla del menú para mostrar las opciones disponibles.

  Se inicia un bucle para permitir al jugador seleccionar una opción válida. Se llama a la función `cambiarOpcion()` para obtener la opción seleccionada por el jugador y mostrar el menú resaltando la opción seleccionada.

  Dentro del bucle, se utiliza una estructura `switch` para manejar la opción seleccionada por el jugador. Si la opción es 1, se cambia el idioma del jugador a español (valor 1). Si la opción es 2, se cambia el idioma del jugador a inglés (valor 2).

  Después de cambiar el idioma del jugador, se muestra un mensaje de pausa para que el jugador pueda leerlo. La función `pause()` se utiliza para mostrar el mensaje.

  Se rompe el bucle para finalizar la función.

  A continuación, se verifica si el idioma del jugador ha cambiado comparando el `idiomaOriginal` con el nuevo idioma seleccionado (`jugador->idioma`). Si el idioma ha cambiado, se llama a la función `cargando()` para mostrar un mensaje de carga.


- **Instrucciones :** `void instrucciones(Jugador *jugador)`.

  La función `instrucciones()` se encarga de mostrar las instrucciones del juego al jugador. Recibe como argumento un puntero a la estructura `Jugador`.

  La función comienza llamando a la función `resetearTeclas()` para reiniciar el estado de las teclas del juego.

  Luego, se verifica el idioma del jugador. Si el idioma es español (valor 1), se limpia la pantalla y se muestra el título del juego utilizando la función `mostrarTitulo()`. A continuación, se muestra el mensaje de instrucciones utilizando la función `mostrarInstrucciones()`.

  Después de mostrar las instrucciones, se llama a la función `pause()` para mostrar un mensaje de pausa y permitir que el jugador presione Enter para continuar.

  Si el idioma es inglés (valor 2), se realiza el mismo proceso pero mostrando los mensajes en inglés.
