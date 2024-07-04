/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"

/**
* @brief returns true when reach last entry in flight table
* @return True when is the last entre of the flight table, False otherwise
*/
static bool is_last_line(unsigned int hour, unsigned int type) {
  return  hour == HOURS - 1u && type == TYPE - 1u;
}

void array_dump(DeliveryTable a) {
  for (unsigned int type = 0u; type < TYPE; ++type) {
    for (unsigned int hour = 0u; hour < HOURS; ++hour) {
      Flight f = a[type][hour];
      fprintf(stdout, "%c: flight with %u %s arrived at %u:00", f.code, f.items_amount, f.type == 0 ? "boxes" : "letters", f.hour - 1);
      if (!is_last_line(hour, type))
      {
        fprintf(stdout, "\n");
      }
    }
  }
}

unsigned int extra_space_fee_cost (DeliveryTable a) {
  unsigned int fee_cost = 0; // Extra fee cost
  unsigned int cant_boxes = 0; // Amount of boxes
  unsigned int cant_letters = 0; // Amount of letters
  for (unsigned int hora = 0u; hora < FEE_CLOSE_HOUR+1; hora++){
    cant_boxes += a[0][hora].items_amount;
    cant_letters += a[1][hora].items_amount;
  }
  // Si la cantidad de cajas supera el maximo permitido, se cobra una penalidad por cada caja extra
  if(cant_boxes > MAX_ALLOWED_BOXES){
    fee_cost += (cant_boxes - MAX_ALLOWED_BOXES) * BOX_PENALTY;
  }
  // Si la cantidad de cartas supera el maximo permitido, se cobra una penalidad por cada carta extra
  if(cant_letters > MAX_ALLOWED_LETTERS){
    fee_cost += (cant_letters - MAX_ALLOWED_LETTERS) * LETTER_PENALTY;
  }
  return fee_cost;
} 


void array_from_file(DeliveryTable array, const char *filepath) {
  FILE *file = NULL;

  file = fopen(filepath, "r");
  if (file == NULL) {
    fprintf(stderr, "File does not exist.\n");
    exit(EXIT_FAILURE);
  }

  char code;
  int i = 0;
  while (!feof(file) ) {
    int res = fscanf(file, " _%c_ ", &code);
    if (res != 1) {
      fprintf(stderr, "Invalid file.\n");
    }
    /* COMPLETAR: Generar y guardar ambos Flight en el array multidimensional */
    Flight flight_boxes = flight_from_file(file, code, 0);
    Flight flight_letters = flight_from_file(file, code, 1);

    array[0][flight_boxes.hour-1] = flight_boxes;
    array[1][flight_letters.hour-1] = flight_letters;

    if (i >= HOURS * TYPE){
      fprintf(stderr, "Invalid file, too many flights.\n");
      exit(EXIT_FAILURE);
    }
  }
}
