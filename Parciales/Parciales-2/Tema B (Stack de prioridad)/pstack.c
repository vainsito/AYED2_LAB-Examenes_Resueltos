#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack {
    unsigned int size;
    struct s_node *first;
};

struct s_node {
    pstack_elem elem;
    struct s_node *next;
    priority_t priority;
};

static struct s_node * create_node(pstack_elem e, priority_t priority) {
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->next = NULL;
    new_node->elem = e;
    new_node->priority = priority;
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

static bool invrep(pstack s) {

    if (s->first==NULL){
        return true;
    }
    bool res = true;
    struct s_node *temp = s->first;
    struct s_node *aux = temp;
    while (temp != NULL && res)
    { 
        while (aux != NULL && res)
        {
            res = res && (temp->priority >= aux->priority);
            aux = aux->next;   
        }
        temp= temp->next;
    }
    return res;
}


pstack pstack_empty(void) {
    pstack s=NULL;
    s = malloc(sizeof(struct s_pstack));
    s->size = 0u;
    s->first = NULL;
    assert (invrep(s));
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
    assert(invrep(s));
    s->size++;
    struct s_node *new_node = create_node(e, priority);
    if (s->first == NULL)
    {
        s->first = new_node;
    }
    else
    {       
        struct s_node *iterador = s->first;
        struct s_node *anterior = iterador;
        if (priority >= iterador->priority)
        {
            s->first = new_node;
            s->first->next = iterador;
        }
        else 
        {
             while (iterador != NULL && priority < iterador->priority)
             {
                anterior = iterador;
                iterador = iterador->next;
             }
            anterior->next = new_node;
            new_node->next = iterador;
        }
    }
    assert(invrep(s) && (!pstack_is_empty(s)));
    return s;
}

bool pstack_is_empty(pstack s) {
    return (s->first == NULL);
}

pstack_elem pstack_top(pstack s) {
    return (s->first->elem);
}

priority_t pstack_top_priority(pstack s) {
    return (s->first->priority);
}

unsigned int pstack_size(pstack s) {
    assert(invrep(s));
    return (s->size);
}

pstack pstack_pop(pstack s) {
    struct s_node *killme = s->first;
    s->first = s->first->next;
    destroy_node(killme);
    return s;
}

pstack pstack_destroy(pstack s) {
    assert(invrep(s));
    s->first = NULL;
    s->size = 0u;
    free(s);
    s = NULL;
    assert(s == NULL);
    return s;
}

