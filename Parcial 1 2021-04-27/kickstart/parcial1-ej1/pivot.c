#include <stdbool.h>
#include <stdio.h>
#include "pivot.h"

// Devuelve true si todos los elementos a la izq de piv son menores o iguales
// y todos los elementos a la derecha de piv son estrictamente mayores
// En otro caso devuelve false.
bool is_pivot(int array[], unsigned int length, unsigned int piv) {
    bool res = true;
    // Parto el arreglo en dos, checkeo a izq y derecha del piv usando if's
    for(unsigned int pos =0; pos < length; pos++){
        // Este if es para chequear que no haya ninguno mayor al a[piv] en la izq
        if((pos< piv) && (array[pos] > array[piv])){
            res = false;
            break;
        }
        // Este else if es para chequear que no haya ninguno <= al a[piv] a la derecha del piv
        else if((pos > piv) && (array[pos] <= array[piv])){
            res = false;
            break;
        }
    }
    return res;
}

// Función main para probar is_pivot
int main() {
    // Ejemplos de arrays para probar
    int array1[] = {1, 2, 3, 4, 5}; 
    int array2[] = {5, 1, 2, 3, 4};
    int array3[] = {1, 3, 2, 4, 5};
    int array4[] = {5, 4, 3, 2, 1};
    int array5[] = {1, 2, 3, 5, 4};

    // Pruebas y resultados esperados
    printf("Test 1: %s\n", is_pivot(array1, 5, 2) ? "true" : "false"); // Debería ser true
    printf("Test 2: %s\n", is_pivot(array2, 5, 0) ? "true" : "false"); // Debería ser false
    printf("Test 3: %s\n", is_pivot(array3, 5, 1) ? "true" : "false"); // Debería ser false
    printf("Test 4: %s\n", is_pivot(array4, 5, 2) ? "true" : "false"); // Debería ser false
    printf("Test 5: %s\n", is_pivot(array5, 5, 3) ? "true" : "false"); // Debería ser false

    return 0;
}

/* 
    IMPORTANTE: COMO COMPILAR.

    1ero: ejecutamos el siguiente comando: gcc -Wall -Werror -Wextra -pedantic -std=c99 -o runner pivot.c
    2do: Corremos el binario que se nos creo de la siguiente forma: ./runner
    3ro: Deberia imprimirse los resultados de los test escritos en main.

*/