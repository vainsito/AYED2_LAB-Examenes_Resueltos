#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "pqueue.h"

struct s_pqueue {
    unsigned int size;
    struct s_node *front;     
};

struct s_node {
    pqueue_elem elem;
    unsigned int priority;
    struct s_node *next;
};

static struct s_node * create_node(pqueue_elem e, unsigned int priority) {
    struct s_node *new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->priority = priority;
    new_node->next = NULL;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);
    node->next = NULL;
    free(node);
    node = NULL;
    assert(node == NULL);
    return node;
}


static bool invrep(pqueue q) {

    if (q->front==NULL){
        return true;
    }
    bool res = true;
    struct s_node *temp = q->front;
    struct s_node *aux = temp;
    while (temp != NULL && res)
    { 
        while (aux != NULL && res)
        {
            res = res && (temp->priority <= aux->priority);
            aux = aux->next;   
        }
        temp= temp->next;
    }
    return res;
}

pqueue pqueue_empty(void) {
    pqueue q=NULL;
    q = malloc(sizeof(struct s_pqueue));
    q->front = NULL;
    q->size = 0u;
    assert(invrep(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, unsigned int priority) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e, priority);
    q->size++;

    if (q->front == NULL){
        q->front = new_node;
    }else
    {
        struct s_node *iterador = q->front;
        struct s_node *anterior = iterador;
        while (iterador != NULL && priority >= iterador->priority){
            anterior = iterador;
            iterador = iterador->next;
        }
        if (priority < pqueue_peek_priority(q)){
            new_node->next = q->front;
            q->front = new_node;
        }
        else
        {
        anterior->next = new_node;
        new_node->next = iterador;
        }
    }
    assert(invrep(q) && !pqueue_is_empty(q));
    return q;
}

bool pqueue_is_empty(pqueue q) {
    return (q->front == NULL);
}

pqueue_elem pqueue_peek(pqueue q) {
    return q->front->elem;
}

unsigned int pqueue_peek_priority(pqueue q) {
    return q->front->priority;
}

unsigned int pqueue_size(pqueue q) {
    assert(invrep(q));
    return q->size;
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q)) ;
    struct s_node *killme = NULL;
    killme = q->front;
    q->front = q->front->next;
    killme = destroy_node(killme);
    assert(invrep(q));
    q->size--;
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    struct s_node *node=q->front;
    while (node != NULL) {
        struct s_node *killme=node;
        node = node->next;
        killme = destroy_node(killme);
    }
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}