#ifndef List_h
#define List_h

//==============================================================================
// DEFINICION Y CREACION DE ESTRUCTURAS
//==============================================================================

typedef struct List List;

List * createList(void);

//==============================================================================
// BUSQUEDA
//==============================================================================

void * firstList(List * list);

void * nextList(List * list);

void * lastList(List * list);

void * prevList(List * list);

//==============================================================================
// INSERCION
//==============================================================================

void pushFront(List * list, const void * data);

void pushBack(List * list, const void * data);

void pushCurrent(List * list, const void * data);

//==============================================================================
// ELIMINACION
//==============================================================================

void * popFront(List * list);

void * popBack(List * list);

void * popCurrent(List * list);

//==============================================================================
// lIMPIEZA
//==============================================================================

void cleanList(List * list);

#endif /* List_h */