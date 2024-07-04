#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "set.h"

struct s_node {
    set_elem elem;
    struct s_node *next;
};

typedef struct s_node * node_t;

struct s_set {
    unsigned int size;
    node_t first;
};

static bool invrep(set s) {
    struct s_node *node;
    bool res = true;
    if(s!=NULL){ // nos fijamos que s no sea vacia
        node = s->first;
        if(node!=NULL){ // nos fijamos que el primer nodo no sea vacio
           while(node->next != NULL){ // recorremos el set
                if(node->elem > node->next->elem){
                    res = false; // aca se romperia la invariante
                }
                node = node->next;
            } 
        }   
    }
    
    return res;
}

static struct s_node *create_node(set_elem e) {
    struct s_node *new_node = malloc(sizeof(struct s_node *));
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

static struct s_node *destroy_node(struct s_node *node) {
    free(node);
    node = NULL;

    return node;
}

/* CONSTRUCTORS */

set set_empty(void) {
    set s = NULL;
    s = malloc(sizeof(struct s_set *));
    s->size = 0;
    s->first = NULL;
    assert(invrep(s));
    return s;
}

set set_add(set s, set_elem e) {
    assert(invrep(s));
    if(!set_member(e, s)){ //chequeamos si ya existe el elemento en el set
        struct s_node *new_node = create_node(e); // creamos el nodo a agregar
        struct s_node *recorrido = NULL; // variable para recorrer el set
        struct s_node *siguiente = NULL; // variable para recorrer el set

        if(s->first==NULL){ // nos fijamos si es el primer elemento a agregar
            s->first = new_node;
        }
        else{
            bool b = true;
            recorrido = s->first;
            if (e < recorrido->elem){ // lo comparamos con el primer elemento del set
                siguiente = recorrido;
                s->first = new_node;
                s->first->next = siguiente;
            }
            else{
                while (recorrido->next != NULL && b){ // lo comparamos hasta el final o que se encuentre su lugar
                    if (e < recorrido->next->elem){
                        b=false; // encontramos un lugar
                    }
                    else{
                        recorrido = recorrido->next; // pasamos al siguiente
                    }
                }
                if (b==false){ // se encontro su lugar entre 2 nodos
                    siguiente = recorrido->next;
                    recorrido->next = new_node;
                    new_node->next = siguiente;
                }
                else{
                    recorrido->next = new_node; // el nodo va al final
                }
            }
        }
            s->size += 1; // aumentamos el tamano en 1
    }
    assert(invrep(s));
    return s;
}

/* OPERATIONS   */
unsigned int set_cardinal(set s) {
    assert(invrep(s));
    return s->size; // devolvemos el tamano del set
}

bool set_is_empty(set s) {
    assert(invrep(s));
    return s->first == NULL;
}

bool set_member(set_elem e, set s) {
    assert(invrep(s));
    node_t node=s->first;
    while (node!=NULL && node->elem < e) {
        node = node->next;
    }
    assert(invrep(s));
    return node!=NULL && node->elem==e;
}


set set_elim(set s, set_elem e) {
    assert(invrep(s));
    struct s_node *actual = NULL, *anterior = NULL;

    if(set_member(e, s)){ // verificamos que exista el elemento e

        actual = s->first;
        while(actual->elem!=e){ // recorremos el set
            anterior = actual;
            actual = actual->next;
        }

        anterior->next = actual->next;
        actual = destroy_node(actual); // elminamos el elemento e
    }
    assert(invrep(s));
    return s;
}

set_elem set_get(set s) {
    assert(invrep(s) && !set_is_empty(s));
    return s->first->elem; // devolvemos un elemento del set
}

set_elem *set_to_array(set s) {
    assert(invrep(s));
    set_elem *s_array = NULL;
    node_t recorrido = s->first;
    s_array = (set_elem*)calloc(set_cardinal(s), sizeof(set_elem)); // asigamos memoria para el arreglo
    if (!set_is_empty(s)){
        for (size_t i = 0; i < set_cardinal(s); i++){ // recooremos el arrelgo para ir agregando elementos
            s_array[i] = recorrido->elem; // vamos agregando los elementos
            recorrido = recorrido->next;
        }
    }
    assert(invrep(s));
    return s_array;
}

set set_destroy(set s) {
    assert(invrep(s));
    struct s_node *node=s->first;

    while (node != NULL) { // recorremos el set hasta el final
        struct s_node *killme=node;
        node = node->next;
        killme = destroy_node(killme); // destruimos el nodo
    }
    free(s); // liberamos el set
    s = NULL;
    assert(s == NULL);
    return s;
}

