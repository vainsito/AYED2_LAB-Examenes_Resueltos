#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "set.h"

typedef int elem_t;

// Nose para que estaba esta funcion, como no tengo la consigna nose si pedian orden de algun elemento
// Como no la uso la comento, pero la daba la catedra
/* static bool elem_lt(elem_t a, elem_t b) {
    return (a < b);
} */


static bool elem_eq(elem_t a, elem_t b) {
    return (a == b);
}

// Clona el elemento dado y retorna el clon
static elem_t elem_clone(elem_t a) {
    return a;
}

static elem_t elem_destroy(elem_t e) {
    return e;
}

static void elem_dump(elem_t e, FILE *fd) {
    fprintf(fd, "%d", e);
}

struct node_t_ {
    elem_t elem;
    struct node_t_ *next;
};

struct set_t_ {
    unsigned int size;
    struct node_t_ *fst;
};

typedef struct node_t_ *node_t;

static node_t create_node(elem_t elem, node_t next) {
    struct node_t_ *new_node = malloc(sizeof(struct node_t_));
    new_node->elem = elem;
    new_node->next = next;
    assert(new_node != NULL);
    return new_node;
}

static node_t destroy_node(node_t node) {
    if (node != NULL)
    {
        free(node);
        node = NULL;
    }
    assert(node == NULL);
    return node;
}


/**
 * Creates an empty set.
 * 
 * @return The newly created set.
 */
set_t set_empty(void) {
    struct set_t_ *new_set = malloc(sizeof(struct set_t_));
    new_set->fst = NULL;
    new_set->size = 0;
    assert(new_set != NULL);
    return new_set;
}

// Tengo que chequear que no exista el elemento antes de agregarlo, si ya existe no hago nada
set_t set_add(set_t set, int element) {
    if (set_belongs(set, element))
    {
        printf("El elemento : %d ya existe en el set!\n", element);
        return set;
    }
    // Lo agrego, como no importa el orden lo agrego al principio
    struct node_t_ *new_node = create_node(element, set->fst);
    set->fst = new_node; // Hago que ahora sea el primero
    set->size++;

    return set;
}

bool set_is_empty(set_t set) {
    return (set->fst == NULL);
}

bool set_belongs(set_t set, int element) {
    bool found = false;
    if (set_is_empty(set))
    {
        return false;
    }
    struct node_t_ *iterator = set->fst;
    while (iterator != NULL && !found)
    {
        if (elem_eq(iterator->elem, element))
        {
            found = true;
        }else{
            iterator = iterator->next;
        }
    }
    return found;  
}

unsigned int set_size(set_t set) {
    return set->size;
}
/**
 * Adds a clone of the given element to the set or frees the element if it already exists in the set.
 * 
 * @param set The set to add the element to.
 * @param elem The element to add to the set.
 * @return The updated set after adding the element.
 */
static set_t add_clone_or_free(set_t set, elem_t elem) {
    if (set_belongs(set, elem))
    {
        elem_destroy(elem);
        return set;
    }
    elem_clone(elem);
    return set_add(set, elem);
    
}


static set_t set_clone(set_t set) {
    set_t new_set = set_empty(); // Creo el nuevo set a clonar
    node_t current = set->fst;
    while (current != NULL) {
        new_set = add_clone_or_free(new_set, current->elem); // Agrego el elemento clonado al nuevo set
        current = current->next;
    }
    return new_set;
}

// La union de dos conjuntos es un conjunto que contiene todos los elementos de ambos conjuntos 
set_t set_union(set_t set1, set_t set2) {
    set_t new_set = set_clone(set1); // Clono el primer set
    node_t current = set2->fst;
    while (current != NULL) {
        new_set = add_clone_or_free(new_set, current->elem); // Agrego el elemento clonado al nuevo set
        current = current->next;
    }
    return new_set;
}

// La intereseccion de dos conjuntos, es un conjunto que contiene los elementos que estan en ambos conjuntos
set_t set_intersect(set_t set1, set_t set2) {
    if (set_is_empty(set1) || set_is_empty(set2))
    {
        printf("Alguno de los conjuntos esta vacio, no se puede hacer la interseccion\n");
        return set_empty();
    }
    set_t new_set = set_empty();
    node_t current = set1->fst;
    while (current != NULL) {
        if (set_belongs(set2, current->elem))
        {
            new_set = add_clone_or_free(new_set, current->elem);
        }
        current = current->next;
    }
    return new_set;
}
// Debo destruir cada nodo y luego el set
set_t set_destroy(set_t set) {
    node_t killme = set->fst;
    node_t iterator = set->fst;
    while (iterator != NULL)
    {
        killme = iterator;
        iterator = iterator->next;
        destroy_node(killme);
        set->size--;
    }
    set->fst = NULL;
    free(set);
    set = NULL;
    assert(set == NULL);
    return set;
}

void set_dump(set_t set, FILE *fd) {
    assert(set != NULL);
    node_t current = set->fst;
    fprintf(fd, "{");
    while (current != NULL) {
        elem_dump(current->elem, fd);
        current = current->next;
        if (current != NULL) {
            fprintf(fd, ",");
        }
    }
    fprintf(fd, "}");
}
