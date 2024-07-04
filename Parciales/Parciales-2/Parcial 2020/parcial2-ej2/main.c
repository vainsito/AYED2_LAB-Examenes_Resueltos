#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "truco.h"

int main()
{
    truco_card carta1;
    truco_card carta2;
    int numero1, numero2;
    char palo1, palo2;
    printf ("Ingrese 2 Cartas: Primero el numero, despues el palo. \n");
    printf ("Numero de la primera \n");
    scanf("%d", &numero1);
    printf ("Palo de la primera \n");
    scanf(" %c", &palo1);
    printf ("Numero de la segunda \n");
    scanf ("%d", &numero2);
    printf ("Palo de la segunda \n");
    scanf(" %c", &palo2);

    if ((numero1 == numero2) && (palo1 == palo2)){
        printf ("NO pueden haber 2 cartas iguales \n");
        exit(EXIT_FAILURE);
    }

    carta1 = truco_card_new(numero1, palo1);
    carta2 = truco_card_new(numero2, palo2);
     
    if (truco_card_win(carta1, carta2)){
        printf("Gana la carta: \n");
        truco_card_dump (carta1);
    } else if (truco_card_win(carta2,carta1)){
        printf("Gana la carta: \n");
        truco_card_dump (carta2);
    } else if (truco_card_tie(carta1,carta2)) {
        printf ("La mano esta empardada \n");
        truco_card_dump(carta1);
        truco_card_dump(carta2);
    }
    
    carta1 = truco_card_destroy (carta1);
    carta2 = truco_card_destroy(carta2);

    return 0;
}
