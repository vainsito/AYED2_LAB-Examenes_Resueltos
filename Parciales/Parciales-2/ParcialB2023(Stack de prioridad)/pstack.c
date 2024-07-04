#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "pstack.h"

struct s_pstack {
    struct s_node *front;
    unsigned int size;
};

struct s_node {
    float average_grade;
    pstack_elem elem;
    unsigned int approved_courses;
    float priority;
    struct s_node *next;
};

float calc_priority (float average_grade, unsigned int approved_courses){
    float res;
    res = (0.3 * (average_grade/MAX_GRADE) + 0.7 * (approved_courses/TOTAL_COURSES));
    return res;
}

static struct s_node *create_node(pstack_elem e, float average_grade, unsigned int approved_courses)
{
    struct s_node *new_node = malloc(sizeof(struct s_node *));
    new_node->priority = calc_priority(average_grade, approved_courses);
    new_node->approved_courses = approved_courses;
    new_node->average_grade = average_grade;
    new_node->elem = e;
    new_node->next = NULL;

    return new_node;
}

static struct s_node *destroy_node(struct s_node *node)
{
    free(node);
    node = NULL;
    return node;
}

static bool invrep(pstack s)
{
    bool res = true;
    if (s->front != NULL){
        struct s_node *aux = s->front;
        while (aux->next != NULL && res){
            if (aux->priority < aux->next->priority){
                res = false;
            }
            else {
                aux = aux->next;
            }
        } 
    }
    return res;
}

pstack pstack_empty(void)
{
    pstack s;
    s = malloc(sizeof(struct s_pstack *));
    s->front = NULL;
    s->size = 0;
    assert(invrep(s) && pstack_is_empty(s));
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, float average_grade, unsigned int approved_courses)
{
    struct s_node *new_node = create_node(e, average_grade, approved_courses);
    s->size++;
    if (s->front == NULL){
        s->front = new_node;
    }
    else {
        struct s_node *iterador = s->front;
        if (s->front->priority <= new_node->priority){
            new_node->next = s->front;
            s->front = new_node;
        } else {
            while (iterador->next != NULL && new_node->priority < iterador->next->priority){
                iterador = iterador->next;
            }
            new_node->next = iterador->next;
            iterador->next = new_node;
        }
    }
    assert(invrep(s) && !pstack_is_empty(s));
    return s;
}

bool pstack_is_empty(pstack s) 
{
    return (s->front == NULL);
}

pstack_elem pstack_top(pstack s) {
   return (s->front->elem);
}

float pstack_top_average_grade(pstack s) {
   return (s->front->average_grade);
}

unsigned int pstack_top_approved_courses(pstack s) {
   return (s->front->approved_courses);
}

float pstack_top_priority(pstack s) {
    return (s->front->priority);
}

unsigned int pstack_size(pstack s) {
   return (s->size);
}

pstack pstack_copy(pstack s)
{
    pstack copy = NULL;
    copy = pstack_empty();
    copy->size = s->size;
    // if s is empty we return the copy
    if (pstack_is_empty(s))
    {
        return copy;
    }

    // copy the front node
    copy->front = create_node(s->front->elem,
                              s->front->average_grade,
                              s->front->approved_courses);

    struct s_node *src = NULL;
    src = s->front->next;

    struct s_node *dest = NULL;
    dest = copy->front;
    while (src != NULL)
    {
        struct s_node *new_node = create_node(src->elem,
                                              src->average_grade,
                                              src->approved_courses);
        dest->next = new_node;
        src = src->next;
        dest = dest->next;
    }

    return copy;
}  

pstack pstack_pop(pstack s) {
    struct s_node *killme = s->front;
    s->front = s->front->next;
    killme = destroy_node(killme);
    assert(invrep(s));
    return s;
}

pstack pstack_destroy(pstack s) {
    assert(invrep(s));
    struct s_node *node = s->front;
    while (node != NULL) {
        struct s_node *killme=node;
        node = node->next;
        killme = destroy_node(killme);
    }
    free(s);
    s = NULL;
    assert(s == NULL);
    return s;
}
