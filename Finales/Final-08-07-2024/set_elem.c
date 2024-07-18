#include <stdio.h>    /* printf()  */
#include <stdbool.h>  /* Type bool */

#include "set_elem.h"  /* Interface */

void set_elem_dump(set_elem e) {
    printf("%d", e);
}

bool set_elem_less(set_elem e1, set_elem e2) {
    return e1 < e2;
}

bool set_elem_eq(set_elem e1, set_elem e2) {
    return e1 == e2;
}

bool set_elem_greater(set_elem e1, set_elem e2) {
    return e1 > e2;
}

