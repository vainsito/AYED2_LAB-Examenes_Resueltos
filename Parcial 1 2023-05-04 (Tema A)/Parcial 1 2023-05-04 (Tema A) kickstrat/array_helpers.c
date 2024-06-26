/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "array_helpers.h"

static const int EXPECTED_DIM_VALUE = 2;

static const char* CITY_NAMES[CITIES] = {
    "Cordoba", "Rosario", "Posadas", "Tilcara", "Bariloche"};
static const char* SEASON_NAMES[SEASONS] = {"low", "high"};

void array_dump(BakeryProductTable a)
{
    for (unsigned int city = 0u; city < CITIES; ++city)
    {
        for (unsigned int season = 0u; season < SEASONS; ++season)
        {
            fprintf(stdout, "%s in %s season: flour (%u,%u) Yeast (%u,%u) Butter (%u,%u) Sales value %u",
                    CITY_NAMES[city], SEASON_NAMES[season], a[city][season].flour_cant,
                    a[city][season].flour_price, a[city][season].yeast_cant,
                    a[city][season].yeast_price, a[city][season].butter_cant,
                    a[city][season].butter_price, a[city][season].sale_value);
            fprintf(stdout, "\n");
        }
    }
}

unsigned int best_profit(BakeryProductTable a)
{
    unsigned int max_profit = 0u;
    // Recorro la tabla de productos, hago el calculo del profit y me quedo con el maximo de la tienda en algun periodo
    for (unsigned int ciudad = 0; ciudad < CITIES-1; ciudad++){
        for (unsigned int season = 0; season < SEASONS-1; season++){
            BakeryProduct product = a[ciudad][season];
            unsigned int product_cost = product.flour_cant * product.flour_price 
                                        + product.yeast_cant*product.yeast_price 
                                        + product.butter_cant * product.butter_price;
            unsigned int profit = product.sale_value - product_cost;
            if (profit > max_profit){
                max_profit = profit;
            }
        }
    }
    
    return max_profit;
}

void array_from_file(BakeryProductTable array, const char* filepath)
{
    FILE* file = NULL;

    file = fopen(filepath, "r");
    if (file == NULL)
    {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    unsigned int city_code, season_code;
    while (!feof(file))
    {
        // Parseo el codigo de ciudad y de temporada
        int res = fscanf(file, "##%u??%u ", &city_code, &season_code);
        if (res != EXPECTED_DIM_VALUE)
        {
            fprintf(stderr, "Invalid file.\n");
            exit(EXIT_FAILURE);
        }
        /* COMPLETAR: Leer y guardar product en el array multidimensional*/
        BakeryProduct product = bakery_product_from_file(file);
        /* Agregar las validaciones que considere necesarias*/
        array[city_code][season_code] = product;
        /* Completar*/
        ++i;
        if (i > CITIES * SEASONS){
            fprintf(stderr, "Invalid file. Array is too long \n");
            exit(EXIT_FAILURE);
        }
    }
    fclose(file);
}
