#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "set.h"
#include "helpers.h"

#define EMPTY 'e'
#define ADD 'a'
#define BELONGS 'b'
#define LENGTH 'l'
#define TOGGLE 't'
#define UNION 'u'
#define INTERSECTION 'i'
#define TEST 'c'
#define QUIT 'q'
#define N 2

char print_menu(int sel) {
    printf("\n\nChoose what you want to do. Options are:\n"
           "\n"
           "\t************************************************\n"
           "\t* e: Empty the set                             *\n"
           "\t* a: Add an element                            *\n"
           "\t* b: Ask if belongs                            *\n"
           "\t* l: Length of the set                         *\n"
           "\t* t: Toggle current set (current is %d)         *\n"
           "\t* u: Show union                                *\n"
           "\t* i: Show intersection                         *\n"
           "\t* c: Check implementation                      *\n"
           "\t* q: Quit                                      *\n"
           "\t************************************************\n"
           "\nPlease enter your choice: ", sel);
    char option = read_char_from_stdin();
    return (option);
}

set_t option_empty(set_t set) {
    set = set_destroy(set);
    set = set_empty();
    return (set);
}

set_t option_add(set_t set) {
    printf("\nInsert an element: ");
    int element = read_int_from_stdin();
    set = set_add(set, element);
    return (set);
}

void option_belongs(set_t set) {
    printf("\nEnter an element: ");
    int element = read_int_from_stdin();
    if (set_belongs(set, element)) {
        printf("\nThe element belongs to the set\n");
    } else {
        printf("\nThe element does NOT belong to the set\n");
    }
}

void option_length(set_t set) {
    printf("\nThe length of the set is %d\n", set_size(set));
}

void dump_all(set_t *sets, int sel) {
    int i = 0;
    printf("\n");
    while (i < N) {
        printf("\n => ");
        set_dump(sets[i], stdout);
        if (i == sel) {
            printf("  << current set");
        }
        i++;
    }
}

// Toggle between set 1 and 2
int option_select(int sel) {
    return (1 - sel);
}

void option_test() {
    set_t s1 = set_empty();
    set_t s2 = set_empty();
    s1 = set_add(s1, 1);
    s1 = set_add(s1, 2);
    s1 = set_add(s1, 3);
    s1 = set_add(s1, 4);
    s2 = set_add(s2, 1);
    s2 = set_add(s2, 2);
    s2 = set_add(s2, 7);
    s2 = set_add(s2, 8);
    assert(set_belongs(s1, 1));
    assert(!set_belongs(s1, 20));
    assert(set_size(s1) == 4);
    assert(set_size(s2) == 4);
    printf("\nSet 1 is: ");
    set_dump(s1, stdout);
    printf("\nSet 2 is: ");
    set_dump(s2, stdout);
    set_t s3=set_union(s1, s2);
    assert(set_size(s3) == 6);
    printf("\nThe union of the sets is: ");
    set_dump(s3, stdout);
    printf("\nThe length of the union is %d", set_size(s3));    
    s3 = set_destroy(s3);
    s3 = set_intersect(s1, s2);
    assert(set_size(s3) == 2);
    printf("\nThe intersection of the sets is: ");
    set_dump(s3, stdout);
    s3 = set_destroy(s3);
    s1 = set_destroy(s1);
    s2 = set_destroy(s2);
}

void option_union(set_t *sets) {
    set_t s1 = set_union(sets[0], sets[1]);
    printf("\nThe union of the sets is: ");
    set_dump(s1, stdout);
    s1 = set_destroy(s1);
}

void option_intersection(set_t *sets) {
    set_t s1 = set_intersect(sets[0], sets[1]);
    printf("\nThe intersection of the sets is: ");
    set_dump(s1, stdout);
    s1 = set_destroy(s1);
}

void empty_all(set_t *set) {
    int i = 0;
    while (i < N) {
        set[i] = set_empty();
        i++;
    }
}

void destroy_all(set_t *set) {
    int i = 0;
    while (i < N) {
        set[i] = set_destroy(set[i]);
        i++;
    }
}

int main(void) {
    set_t sets[N];
    bool exit = false;
    int opt = 0;
    int sel = 0;
    empty_all(sets);
    while (!exit) {
        dump_all(sets, sel);
        opt = print_menu(sel);
        switch (opt) {
            case EMPTY:
                sets[sel] = option_empty(sets[sel]);
                break;
            case ADD:
                sets[sel] = option_add(sets[sel]);
                break;
            case BELONGS:
                option_belongs(sets[sel]);
                break;
            case LENGTH:
                option_length(sets[sel]);
                break;
            case TOGGLE:
                sel = option_select(sel);
                break;
            case UNION:
                option_union(sets);
                break;
            case INTERSECTION:
                option_intersection(sets);
                break;
            case TEST:
                option_test();
                break;
            case QUIT:
                exit = true;
                destroy_all(sets);
                break;
            default:
                break;
        };
    }
}
