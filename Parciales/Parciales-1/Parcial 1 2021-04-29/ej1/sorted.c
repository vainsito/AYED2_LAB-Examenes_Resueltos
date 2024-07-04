#include "sorted.h"
#include <stdbool.h>
#include <stdio.h>

// tengo que devolver el indice hasta el cual esta ordenado el array
unsigned int sorted_until(int array[], unsigned int size) {
    bool sorted = true;
    unsigned int pos = 0;
    while (sorted && pos < size) {
        if (array[pos] > array[pos + 1]) {
            sorted = false;
        }
        pos++;
    }
    return pos-1;
}

// Creo funcion main para probar la funcion sorted_until

int main() {
    // Ejemplos de arrays para probar
    int array1[] = {1, 2, 3, 4, 5}; 
    int array2[] = {5, 1, 2, 3, 4};
    int array3[] = {1, 3, 2, 4, 5};
    int array4[] = {5, 4, 3, 2, 1};
    int array5[] = {1, 2, 3, 5, 4};

    // Pruebas y resultados esperados
    printf("Test 1: %u\n", sorted_until(array1, 5)); // Debería ser 4
    printf("Test 2: %u\n", sorted_until(array2, 5)); // Debería ser 0
    printf("Test 3: %u\n", sorted_until(array3, 5)); // Debería ser 1
    printf("Test 4: %u\n", sorted_until(array4, 5)); // Debería ser 0
    printf("Test 5: %u\n", sorted_until(array5, 5)); // Debería ser 2

    return 0;
}

// Para compilar y correr el programa se debe ejecutar el siguiente comando:
// gcc -Wall -Werror -Wextra -pedantic -std=c99 -o runner sorted.c