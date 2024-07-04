#include <stdbool.h>
#include "even.h"
#include <stdio.h>

// Devuelvo true si el array esta ordenado solo teniendo en cuenta las posiciones pares
bool is_even_sorted(int array[], unsigned int length) {
    bool sorted = true;
    unsigned int pos = 0;
    while (sorted && pos+2 < length) {
        if (pos % 2 == 0 && array[pos] > array[pos + 2]) {
            sorted = false;
        }
        pos++;
    }
    return sorted;
}

// Creo funcion main para probar la funcion is_even_sorted

int main() {
    // Ejemplos de arrays para probar
    int array1[] = {1, 2, 3, 4, 5}; 
    int array2[] = {5, 1, 2, 3, 4};
    int array3[] = {1, 3, 2, 4, 5};
    int array4[] = {5, 4, 3, 2, 1};
    int array5[] = {1, 2, 3, 5, 0};

    // Pruebas y resultados esperados
    printf("Test 1: %s\n", is_even_sorted(array1, 5) ? "true" : "false"); // Debería ser True
    printf("Test 2: %s\n", is_even_sorted(array2, 5) ? "true" : "false"); // Debería ser False
    printf("Test 3: %s\n", is_even_sorted(array3, 5) ? "true" : "false"); // Debería ser True
    printf("Test 4: %s\n", is_even_sorted(array4, 5) ? "true" : "false"); // Debería ser false
    printf("Test 5: %s\n", is_even_sorted(array5, 5) ? "true" : "false"); // Debería ser False

    return 0;
}
