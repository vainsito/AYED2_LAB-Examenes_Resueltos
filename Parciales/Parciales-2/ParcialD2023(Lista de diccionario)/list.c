#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "list.h"

struct _node_t {
  unsigned int key;
  list_value value;
  struct _node_t *next;
};

typedef struct _node_t * node_t;

struct _list_t {
  unsigned int size;
  node_t elems;
};

static bool invrep(list_t list) {
  bool res = true;
  if (!list_is_empty(list)){
    struct _node_t *iterador = list->elems;
    while (iterador->next != NULL && res){
      if (iterador->key >= iterador->next->key){
        res = false;
      }
      else {
        iterador = iterador->next;
      }
    }
  }
  return res;
}

static struct _node_t * create_node(unsigned int key, list_value value) {
  struct _node_t *new_node;
  new_node = malloc(sizeof(struct _node_t));
  new_node->key = key;
  new_node->value = value;
  new_node->next = NULL;

  return new_node;
}

static struct _node_t * destroy_node(struct _node_t *node) {
  free(node);
  node = NULL;
  return node;
}

list_t list_empty(void) {
  list_t s;
  s = malloc(sizeof(struct _list_t));
  s->elems = NULL;
  s->size = 0;
  assert(invrep(s));
  return s;
}

list_t list_add(list_t list, unsigned int key, list_value value) {
  assert(invrep(list));
  struct _node_t *new_node = create_node(key,value); // Corregir, se crea el node aunque exita la clave

  // caso 1: lista vacia
  if (list_is_empty(list)){
    list->elems = new_node;
    list->size++;
  } else {
    node_t elem_actual = list->elems;

    //caso 2: key existe en la lista
    if (list_exists(list, key)){
      while (elem_actual->key != key){
        elem_actual = elem_actual->next;
      }
      elem_actual->value = value;
    } else {
      node_t elem_anterior = list->elems;

      //caso 3: key no existe y es el menor
      if (new_node->key < list->elems->key){
            new_node->next = elem_actual;
            list->elems = new_node;
            list->size++;
      } else {
            bool higher_key = true;

            //itero hasta encontrar un elemento con key menor
            while (elem_actual->next != NULL && higher_key){
                if (new_node->key < elem_actual->key){
                    higher_key = false;
                } else {
                    elem_anterior = elem_actual;
                    elem_actual = elem_actual->next;
                }
            }

            //caso 4: agrego entre el primer y ultimo elemento del list
            if (higher_key == false){
                elem_anterior->next = new_node;
                new_node->next = elem_actual;

            } else if (new_node->key > elem_anterior->key && new_node->key < elem_actual->key){ //caso 5: agrego antes del elem final del list
                new_node->next = elem_actual;
                elem_anterior->next = new_node;

            } else { //caso 6: agrego al final del list
                elem_actual->next = new_node;
            }
            list->size++;
        }
    }
  }
  assert(invrep(list) && !list_is_empty(list));
  return list;
}

unsigned int list_length(list_t list) {
  return (list->size);
}

bool list_is_empty(list_t list) {
  return (list->elems == NULL);
}

bool list_exists(list_t list, unsigned int key) {

  assert(invrep(list));
  node_t cursor = list->elems;
  while (cursor != NULL && cursor->key < key) {
    cursor = cursor->next;
  }
  return cursor != NULL && cursor->key == key;
}


char list_search(list_t list, unsigned int key) {
  list_value res;
  if (list_exists (list,key)){
    struct _node_t *iterador;
    iterador = list->elems;
    while (iterador != NULL && iterador->key > key){
      iterador = iterador->next;
    }
    res = iterador->value;
  }
  return res;
}

list_t list_remove(list_t list, unsigned int key) {
  assert(invrep(list));
  if (list_exists(list,key)){
    if (list->size == 1){
      list->elems = destroy_node(list->elems);
      list->elems = NULL;
      list->size--;
    } else {
      node_t aux_elim = list->elems;
      node_t aux2 = NULL;
      while (aux_elim->key != key){
        aux2 = aux_elim;
        aux_elim = aux_elim->next;
      }
      aux2->next = aux_elim->next;
      aux_elim = destroy_node(aux_elim);
      list->size--;
    }
  }
  assert(invrep(list) && !list_exists(list,key));
  return list;
}

list_t list_remove_all(list_t list) {
  struct _node_t *iterador;
  struct _node_t *anterior;
  iterador = list->elems;
  anterior = iterador;
  if (iterador->next != NULL){
    anterior = destroy_node(anterior);
    anterior = iterador;
    iterador = iterador->next;
  }
 
  list->size = 0;

  return list;
}


list_value* list_to_array(list_t list) {
  list_value* array;
  array = calloc(list->size, sizeof(list_value)); 
  struct _node_t *iterador = list->elems;
  unsigned int i = 0;
  while (iterador != NULL){
    array[i] = iterador->value;
    iterador = iterador->next;
    i++;
  }

  return array;
}

list_t list_destroy(list_t list) {
  list = list_remove_all(list);
  free(list);
  list = NULL;

  return list;
}
