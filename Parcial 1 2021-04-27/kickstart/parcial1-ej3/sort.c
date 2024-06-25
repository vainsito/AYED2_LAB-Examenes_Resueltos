/*
  @file sort.c
  @brief sort functions implementation
*/
#include <stdbool.h>
#include "helpers.h"
#include "sort.h"
#include "song.h"

// Devuelve true si la duracion en segundos de s1 es menor a la de s2
bool goes_before(song_t s1, song_t s2) {
    return s1.seconds <= s2.seconds;
}

bool array_is_sorted(song_t playlist[], unsigned int length) {
    unsigned int i = 0u;
    // Boleano para saber si esta ordenado, si da false se termina el ciclo
    bool sorted = true;
    while (i + 1 < length && sorted) {
        // Uso la funcion goes_before para comparar las canciones
        sorted = goes_before(playlist[i], playlist[i + 1]);
        i = i + 1;
    }
    return sorted;
}

// Chequea si esta ordenado viendo solo las posicoones impares
bool array_is_odd_sorted(song_t playlist[], unsigned int length) {
    // -- Completar --
    unsigned int pos = 1u;
    bool sorted = true;
    // Una forma de hacerlo es ir saltando de a 2 posiciones, empezando desde la 1
    while (pos + 2 < length && sorted) {
        sorted = goes_before(playlist[pos], playlist[pos + 2]);
        pos = pos + 2;
    }
    return sorted;
}

// otra forma de hacerlo es con un condicional chequear que pos sea impar
