#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "position.h"

struct _position {
        unsigned int row;
        unsigned int column;
        unsigned int dimension;
};


position_t position_initial(unsigned int dimension)
{
        // COMPLETE HERE
        position_t pos = malloc(sizeof(struct _position));
        pos->row = 0;
        pos->column = 0;
        pos->dimension = dimension;
        return pos;
}

position_t position_absolute(unsigned int row, unsigned int column,
                             unsigned int dimension)
{
        //COMPLETE HERE
        assert(row < dimension && column < dimension);
        position_t pos_absolute = malloc(sizeof(struct _position));
        pos_absolute->row = row;
        pos_absolute->column = column;
        pos_absolute->dimension = dimension;
        return pos_absolute;
}

position_t position_left(position_t pos)
{
        // COMPLETE HERE
        pos->column = ((pos->column == 0) ? pos->dimension - 1 : pos->column - 1);
        return pos;
}

position_t position_right(position_t pos)
{
    pos->column = (pos->column == pos->dimension - 1) ? 0 : pos->column + 1;
    return pos;
}

position_t position_down(position_t pos)
{
    pos->row = (pos->row == pos->dimension - 1) ? 0 : pos->row + 1;
    return pos;
}

position_t position_up(position_t pos)
{
        // COMPLETE HERE
        pos->row = ((pos->row == 0) ? pos->dimension - 1 : pos->row - 1);
        return pos;
}

unsigned int position_row(position_t pos)
{
        // COMPLETE HERE
        return pos->row;
}

unsigned int position_column(position_t pos)
{
        // COMPLETE HERE
        return pos->column;
}

unsigned int **position_board(position_t pos)
{
    // COMPLETE HERE
    unsigned int **board = malloc(sizeof(unsigned int *) * pos->dimension); // Asignar memoria para el arreglo de punteros
    if (board == NULL) {
        // Manejo de error de asignación de memoria
        return NULL;
    }

    for (unsigned int i = 0; i < pos->dimension; i++)
    {
        board[i] = malloc(sizeof(unsigned int) * pos->dimension); // Asignar memoria para cada fila
        if (board[i] == NULL) {
            // Manejo de error de asignación de memoria para la fila i
            for (unsigned int j = 0; j < i; j++) {
                free(board[j]); // Liberar cada fila asignada hasta el momento
            }
            free(board); // Liberar el arreglo de punteros
            printf("Error de asignación de memoria del tablero\n");
            exit(1);
        }

        for (unsigned int j = 0; j < pos->dimension; j++)
        {
            board[i][j] = 0; // Inicialización segura después de asignar memoria
        }
    }
    board[pos->row][pos->column] = 1; // Marcamos la posición actual
    return board;
}

list_t position_movements(position_t pos)
{
        // COMPLETE HERE
        // Imprimo la posición que me pasaron
        printf("Posición inicial: (%d, %d)\n", pos->row, pos->column);
        list_t movements = list_empty();
        // Primero debo setearme en la columna a la que me quiero mover
        if (pos->column != 0)
        {
/*                 list_append(movements, RIGHT);
                for (unsigned int i = 1; i < pos->column; i++)
                {
                        list_append(movements, RIGHT);
                } */
               list_append(movements, RIGHT);
               list_append(movements, RIGHT);
        }

        // Luego de este for estaria en (0, pos->column)
        // Ahora me tengo que setear en la fila a la que me quiero mover
        printf("Ya me movi a la derecha\n");
        if (pos->row != 0)
        {
                printf("Movimientos a la derecha: %u\n", pos->column);
                for (unsigned int i = 0; i < pos->column; i++)
                {
                list_append(movements, RIGHT);
                }
        }
        
        printf("Ya me movi para abajo\n");
        // Luego de este for estaria en (pos->row, pos->col)
        // Imprimo la lista de movimientos
        list_show(movements);
        return movements;
}

position_t position_destroy(position_t pos)
{
        // COMPLETE HERE
        free(pos);
        return NULL;
}
