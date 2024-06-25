/*
  @file sort.c
  @brief sort functions implementation
*/
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include "helpers.h"
#include "sort.h"
#include "movie.h"

// Devuelvo true si la pelicula s1 tiene menor tiempo de duracion que s2
bool goes_before(movie_t s1, movie_t s2) {
    return s1.runtime <= s2.runtime;
}
// Devuelvo hasta que posicion esta ordenado el array, usando goes_before
unsigned int array_sorted_until(movie_t movielist[], unsigned int size) {
    unsigned int pos = 0;
    bool sorted = true;
    while (sorted && pos+1 < size) {
        if (!goes_before(movielist[pos], movielist[pos + 1])) {
            sorted = false;
        }
        pos++;
    }
    return pos-1;
}

