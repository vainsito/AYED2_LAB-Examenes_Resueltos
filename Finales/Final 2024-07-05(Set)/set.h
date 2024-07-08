#ifndef SET_H
#define SET_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct set_t_ *set_t;

set_t set_empty(void);
set_t set_add(set_t set, int element);
bool  set_is_empty(set_t set);
bool set_belongs(set_t set, int element);
unsigned int set_size(set_t set);
set_t set_union(set_t set1, set_t set2);
set_t set_intersect(set_t set1, set_t set2);
set_t set_destroy(set_t set);
void  set_dump(set_t set, FILE *fd);

#endif
