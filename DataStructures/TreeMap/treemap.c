#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

//==============================================================================
// DEFINICION Y CREACION DE ESTRUCTURAS
//==============================================================================

typedef struct TreeNode TreeNode;

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

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}

TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap * new = (TreeMap *)malloc(sizeof(TreeMap));
    if (new == NULL) return NULL;
    
    new->root = NULL;
    new->current = NULL;
    new->lower_than = lower_than;
    
    return new;

    //new->lower_than = lower_than;
    return NULL;
}

//==============================================================================
// INSERCION
//==============================================================================

// Funcion actualizada
void insertTreeMap(TreeMap * tree, void * key, void * value) {
    if (tree == NULL) return;

    TreeNode * node = createTreeNode(key, value);
    if (node == NULL) return;

    if (tree->root == NULL) {
        tree->root = node;
        return;
    }

    TreeNode * current = tree->root;
    TreeNode * parent = NULL;

    while (current != NULL) {
        parent = current;

        if (is_equal(tree, key, current->pair->key)) {
            // Las claves son iguales, insertar en el subárbol izquierdo
            current = current->left;
        } else if (tree->lower_than(key, current->pair->key)) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    node->parent = parent;

    if (is_equal(tree, key, parent->pair->key)) {
        // Las claves son iguales, insertar en el subárbol izquierdo
        parent->left = node;
    } else if (tree->lower_than(key, parent->pair->key)) {
        parent->left = node;
    } else {
        parent->right = node;
    }
}

//==============================================================================
// ELIMINACION
//==============================================================================

TreeNode * minimum(TreeNode * x){

    if(x->left == NULL)
    {
        return x;
    }
    else
    {
        return minimum(x->left);
    }

}

// Funcion para eliminar el nodo del current del arbol
void eraseTreeMapCurrent(TreeMap * tree) {
    if (tree == NULL || tree->root == NULL || tree->current == NULL) return;

    TreeNode * current = tree->current;

    // Caso 1: El nodo actual no tiene hijos
    if (current->left == NULL && current->right == NULL) {
        if (current->parent == NULL) {
            // Eliminar el nodo raíz
            free(current->pair);
            free(current);
            tree->root = NULL;
        } else {
            // Nodo interno, eliminar referencia del padre
            if (current->parent->left == current) {
                current->parent->left = NULL;
            } else {
                current->parent->right = NULL;
            }
            free(current->pair);
            free(current);
        }
    }
    // Caso 2: El nodo actual tiene un hijo
    else if (current->left == NULL || current->right == NULL) {
        TreeNode * child;
        if (current->left != NULL) {
            child = current->left;
        } else {
            child = current->right;
        }

        if (current->parent == NULL) {
            // Eliminar el nodo raíz con un solo hijo
            free(current->pair);
            free(current);
            tree->root = child;
            child->parent = NULL;
        } else {
            // Nodo interno con un solo hijo, actualizar referencias del padre y del hijo
            if (current->parent->left == current) {
                current->parent->left = child;
            } else {
                current->parent->right = child;
            }
            child->parent = current->parent;
            free(current->pair);
            free(current);
        }
    }
    // Caso 3: El nodo actual tiene dos hijos
    else 
    {
        TreeNode* min = minimum(current->right);

        current->pair->key = min->pair->key;
        current->pair->value = min->pair->value;

        // Eliminar el nodo mínimo sin hacer una llamada recursiva
        if (min->parent->left == min) 
        {
            min->parent->left = min->right;
        } 
        else 
        {
            min->parent->right = min->right;
        }

        if (min->right != NULL) 
        {
            min->right->parent = min->parent;
        }

        free(min->pair);
        free(min);
    }

    tree->current = NULL;
}

//==============================================================================
// BUSQUEDA
//==============================================================================

//prototipado
int countNodesRecursive(TreeNode* node);


// Funcion actualizada
Pair * firstTreeMap(TreeMap * tree) {
    if (tree == NULL || tree->root == NULL) return NULL;

    // Encontrar el nodo más a la izquierda (el nodo más pequeño)
    TreeNode * current = tree->root;
    while (current->left != NULL) {
        current = current->left;
    }

    // Establecer el nodo actual en el árbol
    tree->current = current;

    // Devolver el par clave-valor del nodo actual
    return current->pair;
}

// Funcion actualizada
Pair * nextTreeMap(TreeMap * tree) {
    if (tree == NULL || tree->current == NULL) return NULL;

    // Si el nodo actual tiene un hijo derecho, encontrar el nodo más a la izquierda en ese subárbol
    if (tree->current->right != NULL) {
        TreeNode * current = tree->current->right;
        while (current->left != NULL) {
            current = current->left;
        }
        tree->current = current;
        return current->pair;
    }

    // Si el nodo actual no tiene un hijo derecho, encontrar el primer ancestro ascendente que sea un hijo izquierdo
    TreeNode * current = tree->current;
    TreeNode * parent = current->parent;
    while (parent != NULL && current == parent->right) {
        current = parent;
        parent = parent->parent;
    }
    tree->current = parent;

    // Devolver el par clave-valor del nodo actual
    if (parent != NULL) {
        return parent->pair;
    } else {
        // Se ha alcanzado el final del árbol
        return NULL;
    }
}

Pair* lastTreeMap(TreeMap* tree) {
    if (tree == NULL || tree->root == NULL) return NULL;

    // Encontrar el nodo más a la derecha (el nodo más grande)
    TreeNode* current = tree->root;
    while (current->right != NULL) {
        current = current->right;
    }

    // Establecer el nodo actual en el árbol
    tree->current = current;

    // Devolver el par clave-valor del nodo actual
    return current->pair;
}

Pair* prevTreeMap(TreeMap* tree) {
    if (tree == NULL || tree->current == NULL) return NULL;

    // Si el nodo actual tiene un hijo izquierdo, encontrar el nodo más a la derecha en ese subárbol
    if (tree->current->left != NULL) {
        TreeNode* current = tree->current->left;
        while (current->right != NULL) {
            current = current->right;
        }
        tree->current = current;
        return current->pair;
    }

    // Si el nodo actual no tiene un hijo izquierdo, encontrar el primer ancestro ascendente que sea un hijo derecho
    TreeNode* current = tree->current;
    TreeNode* parent = current->parent;
    while (parent != NULL && current == parent->left) {
        current = parent;
        parent = parent->parent;
    }
    tree->current = parent;

    // Devolver el par clave-valor del nodo actual
    if (parent != NULL) {
        return parent->pair;
    } else {
        // Se ha alcanzado el inicio del árbol
        return NULL;
    }
}

//funcion para ver la cantidad de nodos
int treeSize(TreeMap* tree) {
  if (tree == NULL || tree->root == NULL)
    return 0;

  return countNodesRecursive(tree->root);
}

//====================================================================================================
// OTRAS FUNCIONES
//====================================================================================================

// Funcion para obtener el nodo del raiz del arbol
Pair* obtenerNodoRaiz(TreeMap * tree) {
    if(tree == NULL || tree->root == NULL) return NULL;

    TreeNode* nodoActual = tree->root;

    return nodoActual->pair;
}


//Funcion que cuenta nodos recursivamente
int countNodesRecursive(TreeNode* node) {
  if (node == NULL)
    return 0;

  int countLeft = countNodesRecursive(node->left);
  int countRight = countNodesRecursive(node->right);

  return countLeft + countRight + 1;
}
