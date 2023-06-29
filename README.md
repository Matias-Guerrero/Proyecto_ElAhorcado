# Proyecto_ElAhorcado
 Proyecto de Estructura de Datos, Ingeniería Civil Informática

---

Juego el ahorcado con Estructuras de datos y TDAs.
======

**Preparacion y configuracion del Repositorio**

*   Usamos la aplicación `GitHub Desktop` para crear y actualizar nuestro repositorio local, para evitar usar lo comandos `git fetch` y `git pull`, ya que estos estan integrados en la app.
*   Creamos un repositorio remoto en GitHub, el link es el siguiente: 
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
  
Structs creadas
----

Se nos pidio realizar un proyecto final, en donde elegimos el juego del ahorcado. En donde creamos una aplicación interactiva que ofrece una experiencia personalizada y desafiante a través de niveles progresivos. Incluimos un sistema de puntuaciones para fomentar la competencia entre los jugadores y la opción de guardar y cargar partidas. La aplicación se ejecuta en la terminal, es compatible con diversos dispositivos y tiene una interfaz intuitiva.

Para mantener ordenada nuestro proyecto utilizamos subcarpetas.

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
El programa del juego del Ahorcado comienza con la función main(), que crea un objeto jugador y lo inicializa. A continuación, se crea un árbol binario de búsqueda llamado "arbol_puntajes" utilizando la estructura TreeMap. Este árbol se utiliza para almacenar y organizar los puntajes de los jugadores.

Después de crear el árbol de puntajes, se procede a leer los puntajes existentes desde un archivo y cargarlos en el árbol utilizando la función leerPuntajes(). Esto permite mantener un registro de los puntajes anteriores y compararlos con los nuevos puntajes obtenidos por los jugadores.

A continuación, se configura el tamaño de la pantalla y se oculta el cursor para proporcionar una experiencia de juego más agradable. Luego, se llama a la función menu(), que muestra un menú interactivo donde los jugadores pueden seleccionar diferentes opciones y jugar al juego del Ahorcado.

Una vez que el jugador ha terminado de jugar, se exportan los nuevos puntajes al archivo utilizando la función exportarPuntajes(). Esto asegura que los puntajes actualizados se guarden para futuras sesiones de juego.

Finalmente, el programa devuelve 0 para indicar que se ha ejecutado correctamente. En resumen, el main() del juego del Ahorcado gestiona la configuración inicial, el registro de puntajes, la interfaz de usuario y el flujo general del juego.

Funciones Implementadas
----
- **Nueva Partida :** `void nuevaPartida(Jugador *jugador, TreeMap* arbol_puntajes)`.
  
  La función nuevaPartida() se encarga de iniciar un nuevo juego en el programa del juego del Ahorcado. Recibe dos argumentos: un puntero a la estructura Jugador y un   puntero al árbol binario de búsqueda de puntajes (arbol_puntajes).

  La función comienza por limpiar la pantalla del menú y crear una variable llamada "nombre" para almacenar el nombre del jugador. Luego, se muestra el cursor y se solicita al jugador que ingrese su nombre utilizando la función scanf().

  Después de leer el nombre, se oculta el cursor y se guarda el nombre ingresado en el campo "nombre" de la estructura Jugador. A continuación, se limpia la línea anterior y se inicializan el nivel y los puntos del jugador.

  Luego, se cambia el color de la consola a amarillo para mostrar un mensaje de bienvenida en función del idioma seleccionado por el jugador. Este mensaje se muestra utilizando la función printf() y se pasa el nombre del jugador como argumento.

  Después de mostrar el mensaje de bienvenida, se muestra un mensaje de pausa utilizando la función pause(). Esta función muestra un mensaje en una posición específica de la pantalla y espera a que el jugador presione la tecla Enter para continuar.

  Una vez que el jugador ha presionado Enter, se restaura el color de la consola y se llama a la función cargando() para mostrar una animación de carga durante 2 segundos.

  Finalmente, se llama a la función jugar() para comenzar el juego del Ahorcado, pasando como argumentos el puntero al jugador y el puntero al árbol de puntajes.
