#ifndef _SET_H_
#define _SET_H_

#include <stdbool.h>    /* Definition of bool            */
#include "set_elem.h"   /* Definitions for set_elem type */

typedef struct s_set * set;

set set_empty(void);
/*
 * DESC: Creates a new instance of set with no elements inside
 *
 *   s = set_empty()
 * POS: {s --> set && set_is_empty(s)}
 */

set set_add(set s, set_elem e);
/*
 * DESC: Adds a element <e> to the set <s>. If <e> was already in <s> the
 *       function makes no changes.
 * PRE: {s --> set}
 *   s = set_add(s, e);
 * POS: {s --> set && !set_is_emtpy(s)}
 */

bool set_is_empty(set s);
/*
 * Indicates whether the set <s> is empty.
 * PRE: {s --> set}
 *   b = set_is_empty(s);
 */

unsigned int set_cardinal(set s);
/*
 * DESC: Returns the number of elements in <s>
 * PRE: {s --> set}
 *   n = set_cardinal(s);
 * POS: {(n == 0) == set_is_empty(s)}
 */

bool set_member(set_elem e, set s);
/*
 * DESC: Indicates if the element <e> belongs to the set <s>.
 * PRE: {s --> set}
 *   b = set_member(e, s);
 */

set set_elim(set s, set_elem e);
/*
 * DESC: Eliminates the element <e> from the set <s>. If <e> was not present
 *       in <s>, the function makes no changes.
 * PRE: {s --> set}
 *   s = set_elim(s, e); 
 * POS: {s --> set && !set_member(e, s)}
 */

set_elem set_get(set s);
/*
 * DESC: Returns some element of the set <s>.
 * PRE: {s --> set && !set_is_empty(s)}
 *   e = set_get(s);
 * POS: {set_member(e, s)}
 */

set_elem * set_to_array(set s);
/*
 * DESC: Returns an array with all elements that belong to <s>. The returned
 *       array is stored in dynamic memory and has enough room for
 *       set_cardinal(s) elements. The caller must free the memory when it is
 *       no longer in use.
 * PRE: {s --> set}
 *   array = set_to_array(s);
 * POS: {!set_is_empty(s) ==> (array!=NULL)
 */

void set_dump(set s);
/*
 * DESC: Shows the set elements in stdout
 * PRE: {s --> set}
 *   set_dump(s);
 */

set set_destroy(set s);
/*
 * DESC: Destroys the set <s>, freeing all memory used by the data structure
 * PRE: {s --> set}
 *   s = set_destroy(s);
 * POS: {s == NULL}
 */

#endif /* _SET_H_ */

