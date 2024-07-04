#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "pqueue.h"

struct s_pqueue {
    unsigned int size;
    priority_t min_priority;
    struct s_node **array; 
};

struct s_node {
    pqueue_elem elem;
    struct s_node *next;
};

static struct s_node * create_node(pqueue_elem e) {
    struct s_node* new_node=NULL;
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


static bool invrep(pqueue q) {
    return (q != NULL);
}


pqueue pqueue_empty(priority_t min_priority) {
    pqueue q=NULL;
    q = malloc(sizeof(struct s_pqueue));
    q->array = calloc(min_priority + 1, sizeof(struct s_node *));
    q->size = 0;    
    q->min_priority = min_priority;
    for (priority_t i = 0; i <= min_priority ; i++){
        q->array[i] = NULL;
    }
    assert(invrep(q) && pqueue_is_empty(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, priority_t priority) {
    assert(invrep(q));
    struct s_node *iterador = NULL;
    struct s_node *new_node = NULL;
    new_node = create_node(e);
    q->size++;
    if (q->array[priority] == NULL){
        q->array[priority] = new_node;
    } else {
        iterador = q->array[priority];
        while(iterador->next != NULL){
            iterador = iterador->next;
        }
        iterador->next = new_node;
    }
    assert(invrep(q) && !pqueue_is_empty(q));
    return q;
}

bool pqueue_is_empty(pqueue q) {
    assert(invrep(q));
    bool empty = true;
    for (priority_t i = 0; i <= q->min_priority ; i++){
        if (q->array[i] != NULL){
            empty = false;
        }
    }
    return empty; 
}

pqueue_elem pqueue_peek(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    priority_t i = 0;
    while (q->array[i] == NULL){
        i++;
    } 
    pqueue_elem peek = q->array[i]->elem;
    return peek; 
}

priority_t pqueue_peek_priority(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    priority_t i = 0;
    while (q->array[i] == NULL){
        i++;
    }
    return i; 
}

size_t pqueue_size(pqueue q) {
    assert(invrep(q));
    return q->size; 
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    unsigned int i=0u;
    bool dequeued = false;
    while (i <= q->min_priority && !dequeued){
        if (q->array[i] != NULL){
            struct s_node *aux = q->array[i];
            q->array[i] = q->array[i]->next;
            aux = destroy_node(aux);
            dequeued = true;
        }
        ++i;
    }
    --q->size;
    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    struct s_node *iterador = NULL;
    struct s_node *anterior = NULL;
    for (priority_t i = 0; i <= q->min_priority ; i++){
        iterador = q->array[i]; 
        anterior = iterador;
        while (iterador != NULL){
            anterior = iterador;
            iterador = iterador->next;
            anterior = destroy_node(anterior);
        }
        iterador = destroy_node(iterador);
    }
    free(q->array);
    free(q);

    q = NULL;

    return q;
}