#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue
{
    unsigned int size; //nos dice cuantos elementos tenemos en la queue
    struct s_node *front; //apunta al primer nodo de la lista
};

struct s_node
{
    pqueue_elem elem; //manera de identificar al estudiante
    float average_grade; //promedio de notas del estudiante
    unsigned int approved_courses; //cantidad de cursos aprobados
    float priority; //prioridad dada por la funcion
    struct s_node *next; //nodo 
};


static float calculate_priority(float average_grade, unsigned int approved_courses) {
    float priority = 0.5 * (average_grade/MAX_GRADE) + 0.5 * (approved_courses/TOTAL_COURSES);
    return priority;
}

static struct s_node *create_node(pqueue_elem e, float average_grade,unsigned int approved_courses){

    struct s_node *new_node = malloc(sizeof(struct s_node));
    float priority = calculate_priority(average_grade, approved_courses);
    assert(new_node != NULL);
    new_node->elem = e;
    new_node->priority = priority;
    new_node->approved_courses = approved_courses;
    new_node->average_grade = average_grade;
    new_node->next = NULL;
    return new_node;
}

static struct s_node *destroy_node(struct s_node *node){
    assert(node != NULL);
    free(node);
    node = NULL;
    assert(node == NULL);
    return node;
}


static bool invrep(pqueue q) {
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


pqueue pqueue_empty(void) {
    pqueue q = malloc(sizeof(struct s_node));
    q->front = NULL;
    q->size = 0u;
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, float average_grade, unsigned int approved_courses){
    assert(invrep(q));
    struct s_node *new_node = create_node(e, average_grade, approved_courses); //el nuevo nodo dentro de el se crea su prioridad 
    struct s_node *siguiente =  NULL;
    struct s_node *it = NULL;

    if (q->front == NULL){
        q->front = new_node;
        new_node->next = NULL;
    } else {
        if (new_node->priority > q->front->priority){
            siguiente = q->front;
            new_node->next = siguiente;
            q->front = new_node;
        } else {
            bool brk = true; //nos indica cuando se va a terminar el ciclo
            it = q->front;
            while(it->next != NULL && brk){
                if(new_node->priority > it->next->priority){
                    brk = false;
                } else {
                    it = it->next;
                }
            }
            if (brk == false) {
                siguiente = it->next;
                it->next = new_node;
                new_node->next = siguiente;
            } else {
                it->next = new_node;
            }
        }
    }
    q->size++;
    return q;
}


bool pqueue_is_empty(pqueue q){
    return (q->size == 0 && q->front == NULL);
}


pqueue_elem pqueue_peek(pqueue q){
    assert(invrep(q) && !pqueue_is_empty(q));
    return q->front->elem;
}

float pqueue_peek_average_grade(pqueue q){ //El elemento con mayor prioridad es el que apunta el primer nodo
    return q->front->average_grade;
}

unsigned int pqueue_peek_approved_courses(pqueue q){
    return q->front->approved_courses; //El elemento con mayor prioridad es el que apunta el primer nodo 
}

float pqueue_peek_priority(pqueue q){
    return q->front->priority;
}

unsigned int pqueue_size(pqueue q){
    assert(invrep(q));
    unsigned int size = 0;
    size = q->size;
    return size;
}

pqueue pqueue_copy(pqueue q){
    assert(invrep(q));
    pqueue copy = pqueue_empty(); //donde guardo la copia
    struct s_node *it = q->front;
    while(it != NULL){
        copy = pqueue_enqueue(copy,it->elem,it->average_grade,it->approved_courses); //agrego cada nodo de la cola q a copy
        it = it->next;
    }
    return copy;
}

pqueue pqueue_dequeue(pqueue q){
    assert(invrep(q));
    struct s_node *killme = q->front;
    q->front = q->front->next;
    killme = destroy_node(killme);
    q->size--;
    return q;
}

pqueue pqueue_destroy(pqueue q){
    struct s_node *killme;
    while(q->front != NULL){
        killme = q->front;
        q->front = q->front->next;
        killme = destroy_node(killme);
    }
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}
