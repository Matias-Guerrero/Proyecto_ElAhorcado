#ifndef TREEMAP_h
#define TREEMAP_h

//==============================================================================
// DEFINICION Y CREACION DE ESTRUCTURAS
//==============================================================================

typedef struct TreeMap TreeMap;

typedef struct Pair {
     void * key;
     void * value;
} Pair;

TreeMap * createTreeMap(int (*lower_than_int) (void* key1, void* key2));

//==============================================================================
// INSERCION
//==============================================================================

void insertTreeMap(TreeMap * tree, void* key, void * value); // Funcion actualizada

//==============================================================================
// ELIMINACION
//==============================================================================

void eraseTreeMapCurrent(TreeMap * tree); // Funcion nueva

//==============================================================================
// BUSQUEDA
//==============================================================================

Pair * firstTreeMap(TreeMap * tree); // Funcion actualizada

Pair * nextTreeMap(TreeMap * tree); // Funcion actualizada

Pair* lastTreeMap(TreeMap* tree); //funcion nueva

Pair* prevTreeMap(TreeMap* tree); //funcion nueva

int int treeSize(TreeMap* tree)
//==============================================================================
// OTRAS FUNCIONES
//==============================================================================

Pair* obtenerNodoRaiz(TreeMap * tree);

#endif /* TREEMAP_h */
