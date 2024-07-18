#ifndef _SET_ELEM_H_
#define _SET_ELEM_H_

#include <stdbool.h>   /* Type bool */

typedef int set_elem;

void set_elem_dump(set_elem e);
/*
 * Shows the element `e` on the screen
 *
 */

bool set_elem_less(set_elem e1, set_elem e2);
/* 
 * Indicates whether e1 is less than e2.
 *
 */

bool set_elem_eq(set_elem e1, set_elem e2);
/* 
 * Indicates whether e1 equals to e2.
 *
 */

bool set_elem_greater(set_elem e1, set_elem e2);
/* 
 * Indicates whether e1 is greater than e2.
 *
 */

#endif /* _SET_ELEM_H_ */

