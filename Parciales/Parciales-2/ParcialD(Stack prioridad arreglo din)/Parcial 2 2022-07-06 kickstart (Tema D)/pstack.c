#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack {
    unsigned int size;
    priority_t max_priority;
    struct s_node **array;
};

struct s_node {
    pstack_elem elem;
    struct s_node *next;
};

static struct s_node * create_node(pstack_elem e) {
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    free(node);
    node = NULL;
    return node;
}

static bool invrep(pstack s) {
    return (s != NULL);
}

pstack pstack_empty(priority_t max_priority) {
    pstack s=NULL;
    s = malloc(sizeof(struct s_node));
    s->array = calloc(max_priority + 1, sizeof(struct s_pstack));
    s->max_priority = max_priority;
    s->size = 0;
    assert(invrep(s) && pstack_is_empty(s));
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
    assert(invrep(s));
    struct s_node *new_node = create_node(e);
    if (s->array[priority] == NULL){
        s->array[priority] = new_node;
    } else {
        new_node->next = s->array[priority];
        s->array[priority] = new_node;
    }
    s->size++;
    assert(invrep(s) && !pstack_is_empty(s));
    return s;
}

bool pstack_is_empty(pstack s) {
    assert(invrep(s));
    return (s->size == 0);
}

pstack_elem pstack_top(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    priority_t i = s->max_priority;
    while (s->array[i] == NULL){
        i--;
    }
    return s->array[i]->elem; //como es una pila agrego y saco por izquierda, entonces en el nodo del ultimo indice del arreglo donde se encuentra una pila, agarro el primer elemento al que apunta
}

priority_t pstack_top_priority(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    priority_t i = s->max_priority;
    while (s->array[i] == NULL){
        i--;
    }
    return i; 
}

size_t pstack_size(pstack s) {
    assert(invrep(s));
    return (s->size);
}

pstack pstack_pop(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    priority_t i = s->max_priority;  
    struct s_node *killme = NULL;
    while (s->array[i] == NULL){
        i--;
    }
    killme = s->array[i];
    s->array[i] = s->array[i]->next;
    killme = destroy_node(killme);
    s->size--;
    assert(invrep(s));
    return s;
}

pstack pstack_destroy(pstack s) {
    assert(invrep(s));
    for (priority_t i = 0 ; s->max_priority >= i ; i++){
        if (s->array[i] != NULL){
            while (s->array[i]->next != NULL){ //destruyo todos los nodos del stack
                struct s_node *it = s->array[i];
                s->array[i] = s->array[i]->next;
                it = destroy_node(it);
            }
            s->array[i] = destroy_node(s->array[i]); //destruyo el nodo que apunta al primero del stack
        }
    }
    free(s->array); //libero toda la memoria que calloquee en el arreglo
    free(s); //libero la memoria que malloquee en el stack
    return s;
}
//pensa en todas las variables a las que le asignas memorias y liberalas