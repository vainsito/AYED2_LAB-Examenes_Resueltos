#include <stdlib.h>     /* malloc(), free()... */
#include <stdbool.h>    /* bool type           */
#include <assert.h>     /* assert()            */
#include "key_value.h"  /* key_t               */
#include "dict.h"       /* intarface           */

struct _s_dict {
    // COMPLETAR
    unsigned int dict_length;
    struct _node_t * first;
};

// Internal structure
struct _node_t {
    key_t key;
    value_t value;
    struct _node_t *next;
};

// Funciones para crear y destruir nodos //

struct _node_t * create_node(key_t k, value_t v) {
    struct _node_t *new_node=malloc(sizeof(struct _node_t));
    new_node->key=k;
    new_node->value=v;
    new_node->next=NULL;
    return new_node;
}

struct _node_t *destroy_node(struct _node_t *node) {
    node->key = key_destroy(node->key);
    node->value = value_destroy(node->value);
    free(node);
    node=NULL;
    return node;
}
///////////////////////////////////////////////////

// chequeo que no haya dos claves iguales, que ningun key ni value sea NULL, que el largo sea correcto
static bool invrep(dict_t dict) {
    bool valid = true;
    unsigned int count = 0;
    // Primero veo si el dict es NULL
    if (dict == NULL) {
        printf("Invalid Dict, it cannot be NULL!\n");
        return false;
    }else{ // Voy a hacer un ciclo para chequear claves, keys y largo 
        struct _node_t *iterador = dict->first;
        while (iterador != NULL && valid)
        {
            valid = (iterador->key != NULL && iterador->value != NULL); // Chequeo que las claves y valores de el nodo no sean null
            count++;
            iterador = iterador->next;
        }
        valid = valid && (count == dict->dict_length); // Chequeo que el largo del diccionario coincida con la cant de elems
    }
    return valid;
}
// --- Interface functions ---

dict_t dict_empty(void) {
    // COMPLETAR
    struct _s_dict *new_dict = malloc(sizeof(struct _s_dict));
    if (new_dict == NULL){
        printf("Error asignando memoria para el nuevo dict!\n");
        exit(1);
    }
    new_dict->first = NULL;
    new_dict->dict_length = 0;
    assert(new_dict != NULL && dict_length(new_dict) == 0);
    return new_dict;
}

// Funcion auxiliar que devuelve el nodo de la palabra que queremos
struct _node_t *find_node(dict_t dict, key_t word){
    assert(invrep(dict) && dict_exists(dict, word));
        struct _node_t *iterador = dict->first;\
        struct _node_t *finded = NULL;
        bool found= false;
        while (iterador != NULL && !found)
        {
            if (key_eq(iterador->key, word))
            {
                found = true;
                finded = iterador; // Encuentro la palabra dentro del dict
            }
            iterador = iterador->next;
        }
    return finded;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {
    // COMPLETAR
    assert(invrep(dict));
    // Ahora debo chequear, si el dict no tiene elementos lo agrego de una
    if (dict->first == NULL){
        // primero debo crear el nodo para luego agregarlo
        struct _node_t *new_node = create_node(word, def);
        dict->first = new_node;
        dict->dict_length++;
    }
    else if (dict_exists(dict, word)) { // Si el elemento ya existe, reemplazo la def
        struct _node_t *to_change = find_node(dict, word); // 
        to_change->value = def;
    }
    else{ // Si no existe y la lista tiene mas de un elem, como no importa el orden, lo mas facil es agregarlo al principio
        struct _node_t *new_node = create_node(word, def);
        new_node->next = dict->first;
        dict->first = new_node;
        dict->dict_length++;
    }
    assert(invrep(dict) && dict_exists(dict, word));
    return dict;
}

value_t dict_search(dict_t dict, key_t word) {
    // COMPLETAR
    assert(invrep(dict));
    if (!dict_exists(dict, word))
    {
        printf("Esa palabra no existe, ingrese una valida!\n");
        return NULL;
    }
    
    struct _node_t *node_def = find_node(dict, word);
    value_t def = node_def->value;
    assert(def != NULL);
    return def;
}

bool dict_exists(dict_t dict, key_t word) {
    assert(invrep(dict));
    bool found = false;
    struct _node_t *iterador = dict->first;
    if (dict->dict_length == 1)
    {
        return key_eq(iterador->key, word);
    }
    while (iterador != NULL && !found)
    {
        if (key_eq(iterador->key, word))
        {
            found = true;
        }
        iterador = iterador->next;
    }
    return found;
}

unsigned int dict_length(dict_t dict) {
    // COMPLETAR
    return dict->dict_length;
}

dict_t dict_remove(dict_t dict, key_t word) {
    // COMPLETAR
    assert(invrep);
    struct _node_t *killme;
    if (!dict_exists(dict, word))
    {
        return dict;
    }
    else if (dict->dict_length == 1 && dict_exists(dict, word)) // En este punto la palabra existe y si el dict tiene length 1, esa es la unica palabra
    {
        killme = dict->first;
        killme = destroy_node(killme);
        dict->dict_length--;
        return dict;
    }
    // En este punto podemos asegurar que dict_length > 1 y que la palabra existe, entonces hay q ver como enlazamos el nodo anterior
    struct _node_t *before;
    killme = dict->first;
    while (!key_eq(killme->key, word))
    {
        before = killme;
        killme = killme->next;
    }
    // Cuando salimos del while es pq ya encontramos el nodo
    before->next = killme->next; // Conecto el anterior al siguiente para mantener el orden;
    destroy_node(killme);
    dict->dict_length--;
    return dict;
}

void dict_dump(dict_t dict, FILE *file) {
    assert(invrep(dict));
    for (struct _node_t *check=dict->first; check!=NULL; check=check->next) {
        fprintf(file, "key: ");
        key_dump(check->key, file);
        fprintf(file, "\n");
        fprintf(file, "value: ");
        value_dump(check->value, file);
        fprintf(file, "\n\n");
    }
}

dict_t dict_remove_all(dict_t dict) {
    // COMPLETAR
    if (dict->first == NULL)
    {
        printf("Nothing to remove!\n");
        return dict;
    }
    struct _node_t *iterador = dict->first;
    struct _node_t *killme = iterador;
    while(iterador != NULL){
        killme = iterador;
        iterador = iterador->next;
        destroy_node(killme);
        dict->dict_length--;
    }
    dict->first = NULL;
    assert(dict->dict_length == 0);
    return dict;
}

dict_t dict_destroy(dict_t dict) { 
    assert(invrep(dict));
    dict = dict_remove_all(dict);
    free(dict);
    dict=NULL;
    assert(dict==NULL);
    return dict;
}

