#include "list.h"
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

struct _list
{
    struct _node* head;
    ListSize size;
};

struct _node
{
    elem e;
    struct _node* next;
};

/**
 * @brief Invariante de represetación
 *
 * @param l Lista
 * @return true Si l es una lista válida
 * @return false Si l NO es una lista válida
 */

static bool invrep(list l) {
    bool inv = (l != NULL);
    ListSize length = 0;
    if (inv) {
        struct _node* node = l->head;
        while (node != NULL) {
            length++;
            node = node->next;
        }
        
        inv = inv && l->size == length;
    }
    
    return inv;
}

/**
 * @brief Crea un nodo de la lista nuevo
 *
 * @param e Elemento que contendrá el nodo
 * @return struct _node* Nuevo nodo creado o NULL si no hay memoria
 */
static struct _node* create_node(elem e)
{
    struct _node* res = malloc(sizeof(struct _node));
    if (res != NULL)
    {
        res->e = e;
        res->next = NULL;
    }
    return res;
}

/**
 * @brief Destruye el nodo node
 *
 * @param node Nodo a ser destruido
 * @return struct _node* Devuelve NULL si el nodo se destruyó correctamente
 */
static struct _node* destroy_node(struct _node* node)
{
    if (node != NULL)
    {
        free(node);
        node = NULL;
    }
    assert(node == NULL);
    return node;
}

list list_empty()
{
    list res;
    res = malloc(sizeof(struct _list *));
    res->head = NULL;
    res->size = 0;
    assert(invrep(res));
    return res;
}

list list_addr(list l, elem e)
{
    assert(invrep(l));
    struct _node *new_node = create_node(e);
    if (list_is_empty(l)){
        l->head = new_node;
    }
    else {
        struct _node *iterador = l->head;
        while (iterador->next  != NULL){
            iterador = iterador->next;
        }
        iterador->next = new_node;
    }
    l->size++;
    assert(invrep(l));
    return l;
}

list list_addl(list l, elem e)
{
    //assert(invrep(l));
    struct _node *new_node = create_node(e);
    if (list_is_empty(l)){
        l->head = new_node;
    } else {
        new_node->next = l->head;
        l->head = new_node;
    }
    l->size++;
    assert(invrep(l));
    return l;
}

bool list_is_empty(list l)
{
    assert(invrep(l));
    return (l->size == 0);  
}

elem list_head(list l)
{
    assert(l != NULL && invrep(l) && !list_is_empty(l));
    return (l->head->e);  
}

list list_tail(list l)
{
    assert(!list_is_empty(l));
    struct _node *new_node = l->head;
    if (l->head->next == NULL){
       l->head = NULL; 
    } else {
        l->head = l->head->next;
    }
    new_node = destroy_node(new_node);
    l->size--;
    return l;
}

ListSize list_length(list l)
{
    assert(l != NULL);
    return l->size;
}

void list_print(list l)
{
    struct _node *iterador = l->head;
    while (iterador != NULL){
        printf ("%d", iterador->e);
        iterador = iterador->next;
    }
    iterador = destroy_node(iterador);
    return ;
}

list list_destroy(list l)
{
    assert(l != NULL && invrep(l));
    list d = l;
    while(!list_is_empty(l)) {
        d = list_tail(d);
    }
    l->head = destroy_node(l->head);
    free(l);
    l = NULL;
    assert(l==NULL);
    return l;
}


/* Funciones Anexas */

list list_greater_than(list l, unsigned int n)
{
    struct _node *iterador = l->head;
    list greater;
    greater = list_empty();
    while(iterador->next != NULL){
        if (iterador->e > n){
            greater = list_addr(greater, iterador->e);
        }
        iterador = iterador->next;
    }
    return greater;
}

unsigned int list_greater_than_count(list l, unsigned int n)
{
    struct _node *iterador = l->head;
    unsigned int res = 0;
     while(iterador->next != NULL){
        if (iterador->e > n){
            res++;
        }
        iterador = iterador->next;
    }
    return res;
}

list list_insert_at(list l, unsigned int position, elem e)
{
    struct _node *new_node = create_node(e);
    struct _node *iterador = l->head;
    if (position == 0){
        new_node->next = l->head;
        l->head = new_node;
    } else {
        struct _node *anterior = iterador;
        for (unsigned int i = 1 ; i <= position ; i++){
            anterior = iterador;
            iterador = iterador->next;
        }
        new_node->next = iterador;
        anterior->next = new_node;
    }
    l->size++;
    return l;
}