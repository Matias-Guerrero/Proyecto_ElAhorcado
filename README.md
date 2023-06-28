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

Se nos pidio realizar un proyecto final, en donde elegimos el ahorcado. (complementar con mas info)

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
El programa comienza con la función main() donde se crea al jugador

Dentro de la función main(), 

Funciones Implementadas
----
