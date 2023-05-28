#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "arraylist.h"

//normal array
typedef struct ArrayList {
    void **data;
    int capacity;
    int size;
} ArrayList;

ArrayList *createArrayList(void) {
    ArrayList *nuevo = (ArrayList *)malloc(sizeof(ArrayList));

    assert(nuevo != NULL);

    nuevo->data = malloc(2 * sizeof(void*));
    nuevo->capacity = 2;
    nuevo->size = 0;

    return nuevo;
}

void append(ArrayList * l, void * data){
    assert(l != NULL);

    if(l->size == l->capacity)
    {
        l->data = realloc(l->data, (l->capacity * 2) * sizeof(void*));
        l->capacity *= 2;
    }

    l->data[l->size] = data;
    l->size++;
}

void push(ArrayList * l, void * data, int i){
    assert(l != NULL);

    if(i < 0 || i > l->size)
    {
        return;
    }

    if(l->size == l->capacity)
    {
        l->data = realloc(l->data, (l->capacity * 2) * sizeof(void*));
        l->capacity *= 2;
    }

    for (int k = l->size; k > i; k--)
    {
        l->data[k] = l->data[k - 1];
    }
    
    l->data[i] = data;
    l->size++;
}

void* pop(ArrayList * l, int i){
    assert(l != NULL);

    if(l->size == 0)
    {
        return NULL;
    }

    if(i < 0)
    {
        i = l->size + i;
    }

    if(i < 0 || i > l->size)
    {
        return NULL;
    }

    void* data = l->data[i];

    for (int k = i; k < l->size - 1; k++)
    {
        l->data[k] = l->data[k + 1];
    }

    l->size--;

    return data;
}

void* get(ArrayList * l, int i){
    assert(l != NULL);

    if(i < 0)
    {
        i = l->size + i;
    }

    if(i < 0 || i > l->size)
    {
        return NULL;
    }

    return l->data[i];
}

int get_size(ArrayList * l){
    return l->size;
}

//remove elements
void clean(ArrayList * l){
    l->capacity = 2;
    l->size = 0;
    l->data = realloc(l->data, l->capacity * sizeof(void*));
}
