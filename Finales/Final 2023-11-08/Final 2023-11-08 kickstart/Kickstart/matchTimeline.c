#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "matchTimeline.h"

/* ============================================================================
STRUCTS
============================================================================ */

struct s_node
{
    team team;
    event e;
    time t;
    playerNumber pn;
    struct s_node *next;
};

struct s_matchScore // Tupla para llevar el resultado del partido
{
    unsigned int homeScore;
    unsigned int awayScore;
};

struct s_matchTimeline
{
    struct s_node *head;
    struct s_matchScore score; // Para llevar el resultado del partido
    unsigned int registerSize; // Devuelve la cantidad de eventos registrados
    
};


/* ============================================================================
INVERP & VALIDATION
INVREP: Chequear que la cantidad de registros sea igual a la cantidad de eventos
        Chequear que el time del evento este entre 0 y 90 inclusive
============================================================================ */

static bool invrep(matchTimeline mt)
{
    // COMPLETAR
    bool valid = true;
    unsigned int events = 0;
    if (mt!=NULL){
        struct s_node *aux = mt->head;
        // Bucle para chequear las cosas
        while (aux != NULL && valid){
            if (aux->t > 90)
            {
                valid = false;
                printf("El tiempo del evento no esta entre 0 y 90\n");
            }
            aux = aux->next;
            events++;
        }
        valid = valid && mt->registerSize == events;
    }
    return (mt==NULL ? false : valid); // Si mt es NULL, no es válido, 
}

bool matchTimeline_is_time_and_score_valid(matchTimeline mt)
{
    assert(mt != NULL);
    // COMPLETAR
    bool valid = true;
    unsigned int home_register_score = 0;
    unsigned int away_register_score = 0;
    struct s_node *aux = mt->head;
    while (aux->next != NULL && valid)
    {
        // Bucle para verificar que los eventos estén ordenados cronológicamente
        if (aux->t > aux->next->t)
        {
            valid = false;
            printf("Los eventos no están ordenados cronológicamente\n");
        }
        // Cuento la cantidad de registros de goles de home y away
        if(aux->e == Goal)
        {
            if(aux->team == Home)
            {
                home_register_score++;
            }
            else
            {
                away_register_score++;
            }
        }
        aux = aux->next;
    }
    valid = valid && mt->score.awayScore == away_register_score && mt->score.homeScore == home_register_score;
    return valid;
}
/* ============================================================================
CONSTRUCTOR
============================================================================ */

matchTimeline matchTimeline_empty(void)
{
    matchTimeline mt = NULL;
    mt = malloc(sizeof(struct s_matchTimeline));
    mt->head = NULL;
    mt->registerSize = 0;
    mt->score.awayScore = 0;
    mt->score.homeScore = 0;
    assert(invrep(mt));
    return mt;
}

/* ============================================================================
INSERTION
============================================================================ */

static struct s_node *create_node(team team, event e, time t, playerNumber pn)
{
    struct s_node *new_node = NULL;
    // COMPLETAR
    new_node = malloc(sizeof(struct s_node));
    if(new_node == NULL){
        printf("Error asignando memoria para un nuevo nodo\n");
        exit(1);
    }
    new_node->team = team;
    new_node->e = e;
    new_node->t = t;
    new_node->pn = pn;
    new_node->next = NULL;
    return new_node;
}

// Funcion auxiliar para agregar un evento
static void add_event(matchTimeline mt, struct s_node *event){
    if (mt->head == NULL){
        mt->head = event;
    }
    else{
        struct s_node *iterador = mt->head;
        while(iterador->next !=NULL){
            iterador = iterador->next;
        }
        iterador->next = event;
    }
    mt->registerSize++;
}

/* ============================================================================
GOAL
============================================================================ */

matchTimeline matchTimeline_score_goal(matchTimeline mt, team team, time t, playerNumber pn)
{
    assert(invrep(mt));
    
    // COMPLETAR
    struct s_node *goal_event = create_node(team, Goal, t, pn);
    add_event(mt, goal_event);
    printf("Evento de gol agregado\n");
    // Operacion ternaria para asignar los goles al marcador
    (team == Home ? mt->score.homeScore++ : mt->score.awayScore++);
    assert(invrep(mt));
    return mt;
}

/* ============================================================================
THE CARDS
============================================================================ */

static bool is_player_amonested(matchTimeline mt, playerNumber pn){
    assert(mt != NULL);
    bool found = false;
    struct s_node *iterator = mt->head;
    while(iterator && !found){
        if (iterator->e == YellowCard && iterator->pn == pn)
        {
            found = true;
        }
        iterator = iterator->next;
    }
    return found;
}

matchTimeline matchTimeline_receive_yellowCard(matchTimeline mt, team team, time t, playerNumber pn)
{
    assert(invrep(mt));
    // COMPLETAR
    struct s_node *yellow_event = create_node(team, YellowCard, t, pn);
    bool is_amonested = is_player_amonested(mt, pn);
    if (is_amonested == true) { 
        add_event(mt, yellow_event);
        matchTimeline_receive_redCard(mt, team, t, pn);
        printf("El jugador ya tiene una tarjeta amarilla, se le saca tarjeta roja\n");    
    }else{
        add_event(mt, yellow_event);
        printf("Evento de tarjeta amarilla agregado\n");
    }
    return mt;
}

matchTimeline matchTimeline_receive_redCard(matchTimeline mt, team team, time t, playerNumber pn)
{
    assert(invrep(mt));
    // COMPLETAR
    struct s_node *red_event = create_node(team, RedCard, t, pn);
    add_event(mt, red_event);
    printf("Evento de tarjeta roja agregado\n");
    return mt;
}

/* ============================================================================
SCORE
============================================================================ */

unsigned int matchTimeline_get_score(matchTimeline mt, team team)
{
    assert(invrep(mt));
    // COMPLETAR
    unsigned int score = 0;
    score = (team == Home ? mt->score.homeScore : mt->score.awayScore);
    return score;
}

/* ============================================================================
SIZE
============================================================================ */

unsigned int matchTimeline_size(matchTimeline mt)
{
    assert(invrep(mt));
    // COMPLETAR
    return mt->registerSize;
}

/* ============================================================================
PRINT
============================================================================ */

void matchTimeline_print(matchTimeline mt)
{
    fprintf(
        stdout, "            Home %u -  %u Away \n", 
        matchTimeline_get_score(mt, Home), 
        matchTimeline_get_score(mt, Away)
    );

    struct s_node *aux = mt->head;
    while (aux != NULL)
    {
        unsigned int t = aux->t;
        char *e;
        switch (aux->e)
        {
        case Goal:
            e = "    Goal   ";
            break;
        case YellowCard:
            e = "Yellow Card";
            break;
        case RedCard:
            e = "  Red Card ";
            break;
        }
        unsigned int pn = aux->pn;

        if (aux->team == Home) {
            fprintf(stdout, "%u - %s - %u' \n", pn, e, t);
        }
        else {
            fprintf(stdout, "                   %u' - %s - %u \n", t, e, pn);
        }

        aux = aux->next;
    }
}

/* ============================================================================
ARRAY
============================================================================ */

event *matchTimeline_events_array(matchTimeline mt)
{
    if (mt == NULL || mt->registerSize == 0) {
            return NULL; // Retorna NULL si el timeline está vacío o no existe
        }

        // Asigna memoria para un arreglo de eventos, no de nodos
        event *array = calloc(mt->registerSize, sizeof(event));
        if (array == NULL) {
            printf("Error asignando memoria para el arreglo\n");
            exit(1);
        }

        struct s_node *iterator = mt->head;
        for (unsigned int i = 0; i < mt->registerSize && iterator != NULL; i++) {
            array[i] = iterator->e; // Copia el tipo de evento en el arreglo
            iterator = iterator->next;
        }
    return array;
}

/* ============================================================================
DESTRUCTOR!
============================================================================ */

static struct s_node *destroy_node(struct s_node *node)
{
    if (node != NULL)
    {
        free(node);
    }
    return NULL; // Retorna NULL para evitar el uso de punteros a memoria liberada
}

matchTimeline matchTimeline_destroy(matchTimeline mt)
{
    assert(invrep(mt));

    struct s_node *iterador = mt->head;
    struct s_node *next;

    while(iterador != NULL){
        next = iterador->next; // Guarda el siguiente nodo antes de liberar el actual
        iterador = destroy_node(iterador); // Liberar el nodo actual y establecer iterador a NULL
        iterador = next; // Avanza al siguiente nodo
    }

    free(mt); // Libera la estructura de matchTimeline
    mt = NULL; // Establece mt a NULL para evitar el uso después de liberar

    return mt; // Retorna NULL
}
