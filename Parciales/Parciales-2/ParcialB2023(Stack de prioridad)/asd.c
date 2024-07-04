#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack {
    struct s_node *front;
};

struct s_node {
    pstack_elem elem;
    float average_grade;
    unsigned int approved_courses;
    float priority;
    struct s_node *next;
};


static float calculate_priority(float average_grade,
                                unsigned int approved_courses)
{
    float priority = 0.3 * (average_grade / MAX_GRADE) +
                     0.7 * (approved_courses / TOTAL_COURSES);
    return priority;
}

static struct s_node *create_node(pstack_elem e,
                                  float average_grade,
                                  unsigned int approved_courses)
{
    // first calculate priority
    float priority = calculate_priority(average_grade, approved_courses);

    struct s_node *new_node = malloc(sizeof(struct s_node));
    assert(new_node != NULL);
    new_node->elem = e;
    new_node->average_grade = average_grade;
    new_node->approved_courses = approved_courses;
    new_node->priority = priority;

    new_node->next = NULL;
    return new_node;
}

static struct s_node *destroy_node(struct s_node *node)
{
    node->next = NULL;
    free(node);
    node = NULL;
    return node;
}

static bool invrep(pstack s)
{
    bool inv = (s->front == NULL || s->front != NULL);
    return inv;
}

pstack pstack_empty(void)
{
    pstack s=NULL;
    /*
     * COMPLETAR
     *
     */
    s = malloc(sizeof(struct s_pstack));
    s->front = NULL;

    assert(invrep(s) && pstack_is_empty(s));
    return s;
}

pstack pstack_push(pstack s,
                   pstack_elem e,
                   float average_grade,
                   unsigned int approved_courses)
{
    assert(invrep(s));
    struct s_node *new_node = create_node(e, average_grade, approved_courses);
    if (s->front==NULL) 
    {
        s->front = new_node;
    }
    else
    {
        /*
         * COMPLETAR
         *
         */
        if (s->front->priority <= new_node->priority) {
            new_node->next = s->front;
            s->front = new_node;
        } 
        else
        {
            struct s_node * aux = s->front;
            while (aux->next != NULL && aux->next->priority > new_node->priority) {
                aux = aux->next;
            }
            new_node->next = aux->next;
            aux->next = new_node;
        }
    }
    assert(invrep(s) && !pstack_is_empty(s));
    return s;
}

bool pstack_is_empty(pstack s) 
{
    assert(invrep(s));
    return s->front == NULL;
}

pstack_elem pstack_top(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    return s->front->elem;
}

float pstack_top_average_grade(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    return s->front->average_grade;
}

unsigned int pstack_top_approved_courses(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    return s->front->approved_courses;
}

float pstack_top_priority(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    return s->front->priority;
}

unsigned int pstack_size(pstack s) {
    assert(invrep(s));
    unsigned int size=0;
    struct s_node *node=s->front;
    while (node != NULL) {
        node = node->next;
        size++;
    }

    return size;
}

pstack pstack_copy(pstack s)
{
    pstack copy = NULL;
    copy = pstack_empty();

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
    assert(invrep(s) && !pstack_is_empty(s));
    struct s_node * killme = s->front;
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
