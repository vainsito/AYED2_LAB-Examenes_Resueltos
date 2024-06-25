#include <stdbool.h>
#include <stdio.h>

#include "odd.h"


// Devuelve true si las posiciones impares estan ordenadas
// Osea por ej [0, 1, 3, 9, 7] es true porque 1 < 9
// Ej [1, 10, 3, 2] Es false, porque 10 > 2
bool is_odd_sorted(int array[], unsigned int length) {
    bool res = true;

    for(unsigned int pos=0; pos< length; pos++){
        // Chequeo las posiciones impares
        if((pos%2!= 0) && (pos+2 < length)){
            res = (array[pos] < array[pos+2]) && res;
        }
    }
    return res;
}


// Función main para probar is_odd_sorted
int main() {
    // Ejemplos de arrays para probar
    int array1[] = {0, 1, 3, 9, 7}; // Debería ser true
    int array2[] = {1, 10, 3, 2};   // Debería ser false
    int array3[] = {1, 2, 3, 4, 5}; // Debería ser true
    int array4[] = {5, 3, 4, 1, 2}; // Debería ser false
    int array5[] = {1, 3, 2, 5};    // Debería ser true

    // Pruebas y resultados esperados
    printf("Test 1: %s\n", is_odd_sorted(array1, 5) ? "true" : "false");
    printf("Test 2: %s\n", is_odd_sorted(array2, 4) ? "true" : "false");
    printf("Test 3: %s\n", is_odd_sorted(array3, 5) ? "true" : "false");
    printf("Test 4: %s\n", is_odd_sorted(array4, 5) ? "true" : "false");
    printf("Test 5: %s\n", is_odd_sorted(array5, 4) ? "true" : "false");

    return 0;
}

// Compilar igual que en el ej 1.