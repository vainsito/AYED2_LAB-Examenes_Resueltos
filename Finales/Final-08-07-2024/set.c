#include <stdlib.h>   /* malloc(), free(), NULL  */
#include <stdbool.h>  /* Definition of bool      */
#include <stdio.h>    /* printf()                */
#include <assert.h>   /* assert()                */

#include "set.h"      /* Iterface */

struct s_node {
    set_elem elem;
    struct s_node *next;
};

typedef struct s_node * node_t;

struct s_set {
    /*
     * COMPLETAR
     */
    unsigned int size; // Indica el tam del conjunto
    node_t first;
};

/* Creates a single node in dynamic memory containing the element <e>. */
static node_t
create_node(set_elem e) {
    /* COMPLETAR */
    struct s_node *new_node = malloc(sizeof(struct s_node));
    new_node->elem = e; 
    new_node->next = NULL;
    assert(new_node != NULL);
    return new_node;
    
}

/* Destroys a single node */
static node_t
destroy_node(node_t node) {
    /* COMPLETAR */
    if (node != NULL){
        free(node);
        node = NULL;
    }
    assert(node == NULL);
    return node;
    
}

/* Representation invariant */
// En la inv voy a chequear que los elementos cumpla que e1<e2<e2....<en
// Chequeo tambien que la cantidad de elementos recorridos sea igual al size del set
static bool invrep(set s) {
    struct s_node *iterador;
    bool res = true;
    if(s != NULL){ // nos fijamos que s no sea vacia
        iterador = s->first;
        if(iterador != NULL){ // nos fijamos que el primer nodo no sea vacio
           while(iterador->next != NULL){ // recorremos el set
                if(iterador->elem > iterador->next->elem){
                    res = false; // aca se romperia la invariante
                }
                iterador = iterador->next;
            } 
        }   
    }
    return res;
}

/* CONSTRUCTORS */

set set_empty(void) {
    /* COMPLETAR */
    struct s_set *new_set = malloc(sizeof(struct s_set));
    new_set->first = NULL;
    new_set->size = 0;
    assert(new_set != NULL);
    return new_set; 
}

set set_add(set s, set_elem e) {
    /* COMPLETAR */
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
    /* COMPLETAR */
    assert(invrep(s));
    return s->size;
}

bool set_is_empty(set s) {
    /* COMPLETAR */
    return (s->first == NULL);
}

bool set_member(set_elem e, set s) {
    /* COMPLETAR */
    assert(invrep(s));
    node_t iterador=s->first;
    while (iterador!=NULL && iterador->elem < e) {
        iterador = iterador->next;
    }
    assert(invrep(s));
    return (iterador!=NULL && iterador->elem==e);
}

set set_elim(set s, set_elem e) {
    /* COMPLETAR */
    assert(invrep);
    if (!set_member(e, s)){ // Si el elemento no existe devuelvo el set como estaba
        printf("El elemento: %d no existe en el set!\n", e);
        return s;
    }
    
    struct s_node *actual = NULL;
    struct s_node *anterior = NULL;
    actual = s->first;
    if (e == s->first->elem){ // Si el elemento es el primero del set, lo elimino
        s->first = actual->next;
        actual = destroy_node(actual);
        s->size--;
        return s;
    }
    while(actual->elem != e){ // recorremos el set
        anterior = actual;
        actual = actual->next;
    }
    anterior->next = actual->next;
    actual = destroy_node(actual); // elminamos el elemento e
    s->size--;
    assert(invrep(s));
    return s;
}

set_elem set_get(set s) {
    /* COMPLETAR */
    assert(invrep(s) && !set_is_empty(s));
    return s->first->elem;
}

set_elem* set_to_array(set s) {
    /* COMPLETAR */
    assert(invrep(s));
    set_elem *s_array = NULL;
    struct s_node *recorrido = s->first;
    s_array = (set_elem*)calloc(set_cardinal(s), sizeof(set_elem)); // asigamos memoria para el arreglo
    if (!set_is_empty(s)){
        for (size_t i = 0; i < set_cardinal(s); i++){ // recorremos el arreglo para ir agregando elementos
            s_array[i] = recorrido->elem; // vamos agregando los elementos
            recorrido = recorrido->next;
        }
    }
    assert(invrep(s));
    return s_array;
}

void set_dump(set s) {
    assert(invrep(s));
    node_t node=s->first;
    if (node==NULL) {
        printf("{}");
    } else {
        printf("{");
        set_elem_dump(node->elem);
        while (node->next != NULL) {
            printf(", ");
            set_elem_dump(node->next->elem);
            node = node->next;
        }
        printf("}");
    }
}

set set_destroy(set s) {
    /* COMPLETAR */
    assert(invrep(s));
    struct s_node *iterador=s->first;

    while (iterador != NULL) { // recorremos el set hasta el final
        struct s_node *killme=iterador;
        iterador = iterador->next;
        killme = destroy_node(killme); // destruimos el nodo
    }
    free(s); // liberamos el set
    s = NULL;
    assert(s == NULL);
    return s;
}

