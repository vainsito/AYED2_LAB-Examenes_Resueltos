#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue
{
    unsigned int size;
    struct s_node *front;
};

struct s_node
{
    pqueue_elem elem;
    float average_grade;
    unsigned int approved_courses;
    float priority;
    struct s_node *next;
};


static float calculate_priority(float average_grade,
                                unsigned int approved_courses)
{
    float priority;
    priority = 0.5 * (average_grade/MAX_GRADE) + 0.5 * (approved_courses/TOTAL_COURSES);
    if (priority>1){
        priority = 1;
    }
    if (priority < 0){
        priority = 0;
    }
    return priority;
}

static struct s_node *create_node(pqueue_elem e,
                                  float average_grade,
                                  unsigned int approved_courses)
{

    struct s_node *new_node = NULL;
    float priority = calculate_priority(average_grade, approved_courses);
    // Completar
    new_node = malloc(sizeof(struct s_node));
    new_node->elem = e;
    new_node->average_grade = average_grade;
    new_node->approved_courses = approved_courses;
    new_node->priority = priority;
    new_node->next = NULL;
    assert(new_node != NULL);
    return new_node;
}

static struct s_node *destroy_node(struct s_node *node)
{
    assert(node != NULL);
    free(node);
    node = NULL;
    assert(node == NULL);
    return node;
}

static bool invrep(pqueue q)
{
    static bool valid = true;
    //si pqueue tiene un solo elemento, es un pqueue valido, si es NULL, igualmente
    if (!pqueue_is_empty(q) && q->size>1){
        struct s_node *aux = NULL;
        aux = q->front;
        while (aux->next != NULL && valid){
            valid = aux->priority >= aux->next->priority; //chequeo que la prioridad del elem sig sea mayor, si es menor, retorno false;
            aux = aux->next;
        }
    }
    return valid;
}

pqueue pqueue_empty(void)
{
    pqueue q=NULL;
    q = malloc(sizeof(struct s_pqueue));
    q->size = 0u;
    q->front = NULL;
    assert(invrep(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q,
                      pqueue_elem e,
                      float average_grade,
                      unsigned int approved_courses)
{
    assert(invrep(q));
    struct s_node *new_node = create_node(e, average_grade, approved_courses);
    //caso 1: queue vacio
    if (pqueue_is_empty(q)){
        q->front = new_node;
    } else {
        struct s_node *recorrido = q->front;
        struct s_node *auxiliar = q->front;
        //caso 2: agrego al frente del queue
        if (new_node->priority > q->front->priority){
            q->front = new_node;
            new_node->next = recorrido;
        } else {
            bool lower_priority = true;
            //itero hasta encontrar un elemento con prioridad mayor o hasta haber recorrido todo el queue
            while (recorrido->next != NULL && lower_priority){
                if (new_node->priority > recorrido->priority){
                    lower_priority = false;
                } else {
                    auxiliar = recorrido;
                    recorrido = recorrido->next;
                }
            }
            //caso 3: agrego entre el primer y ultimo elemento del queue, q.size>1
            if (lower_priority == false){
                auxiliar->next = new_node;
                new_node->next = recorrido;
            //caso 4: agrego al final del queue, q.size >1
            } else if (new_node->priority < auxiliar->priority && new_node->priority>recorrido->priority){
                new_node->next = recorrido;
                auxiliar->next = new_node;
            } else {
                recorrido->next = new_node;
            }
        }
    }
    q->size++;
    assert(invrep(q) && !pqueue_is_empty(q));
    return q;
}

bool pqueue_is_empty(pqueue q)
{
    return q->size == 0;
}


pqueue_elem pqueue_peek(pqueue q)
{
    assert(invrep(q) && !pqueue_is_empty(q));
    return q->front->elem;
}

float pqueue_peek_average_grade(pqueue q)
{
    assert(invrep(q) && !pqueue_is_empty(q));
    return q->front->average_grade;
    assert(invrep(q));
}

unsigned int pqueue_peek_approved_courses(pqueue q)
{
    assert(invrep(q) && !pqueue_is_empty(q));
    return q->front->approved_courses;
    assert(invrep(q));
}

float pqueue_peek_priority(pqueue q)
{
    assert(invrep(q) && !pqueue_is_empty(q));
    return q->front->priority;
    assert(invrep(q));
}

unsigned int pqueue_size(pqueue q)
{
    assert(invrep(q));
    unsigned int size = 0;
    size = q->size;

    return size;
}

pqueue pqueue_copy(pqueue q)
{
    assert(invrep(q));
    pqueue copy = NULL;
    copy = pqueue_empty();
    if (q->front != NULL){
        struct s_node *aux = q->front;
        //asigno a copy el front y size
        while (aux != NULL){
            copy = pqueue_enqueue(copy,aux->elem,aux->average_grade,aux->approved_courses);
            aux = aux->next;
        }
    }
    
    assert(invrep(copy));
    return copy;
}

pqueue pqueue_dequeue(pqueue q)
{
    assert(invrep(q) && !pqueue_is_empty(q));
    if (q->size == 1){
        destroy_node(q->front);
        q->front = NULL;
    } else {
        struct s_node *aux = NULL;
        aux = q->front;
        q->front = q->front->next;
        aux = destroy_node(aux);
    }
    --q->size;
    return q;
    assert(invrep(q));
}

pqueue pqueue_destroy(pqueue q)
{
    assert(invrep(q)); 
    struct s_node *aux = NULL;
    while(q->front != NULL){
        aux = q->front;
        q->front = q->front->next;
        destroy_node(aux);
    }
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}
