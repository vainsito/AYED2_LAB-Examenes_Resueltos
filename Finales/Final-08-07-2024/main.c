/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* Then, this project's includes, alphabetically ordered */
#include "set.h"
#include "set_helpers.h"

/* Define max elements for remove operation in command line arguments */
#define MAX_ELIM 10

void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path> [elim_elem1] [elim_elem2] ... [elim_elem%d]\n\n"
           "Loads elements given in a file on disk into a set and perform remove operations.\n"
           "\n"
           "The input file must have the following format:\n\n"
           " * One line that must contain the elements"
           " separated by one or more spaces. Each member must be an integer."
           "\n\n"
           "In other words, the file format is:\n"
           "<elem_1> <elem_2> ... <elem_N>\n\n"
           "After loading, the program begins to eliminate from the constructed "
           "set each element specified in the parameters `elim_elem1`, "
           "elim_elem2`, ..., `elim_elem%d`. If there are no such parameters, no elimination "
           "actions will be performed.\n\n"
           ""
           "",
           program_name, MAX_ELIM, MAX_ELIM);
}

char *parse_filepath(int argc, char *argv[], int *arg_nelim, int elim_elems[MAX_ELIM]) {
    /* Parse the filepath given by command line argument. */
    char *filepath = NULL;
    int nelim = 0;
    // Check arguments
    if (argc < 2 || argc > 2 + MAX_ELIM) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }
    // Take filepath parameter from command line arguments
    filepath = argv[1];
    // Calculate numer of elements in arguments
    nelim = argc - 2;
    // Take elements from command line arguments for later removal operations
    for (int i=0; i < nelim; i++) {
        elim_elems[i] = atoi(argv[i + 2]);
    }
    // Output
    *arg_nelim=nelim;
    return filepath;
}

int main(int argc, char *argv[]) {
  char *filepath = NULL;
  int elim_elems[MAX_ELIM];
  int nelims=0;
  /* Parse command line arguments */
  filepath = parse_filepath(argc, argv, &nelims, elim_elems);
  /* Load data from file and construct a set instance */
  set s = set_from_file(filepath);
  /* Get the set size*/
  unsigned int size=set_cardinal(s);
  /* Show set content */
  printf("Set of elements read in the file: ");
  set_dump(s);
  printf("\n\n");
  /* Show amount of elements in the set */
  printf("The file '%s' has %u unique elements\n", filepath, size);
  /* Check that elements are found in the set */
  int *elems=set_to_array(s);
  for (unsigned int i=0; i < size; i++) {
      printf("%d [%s]%s", elems[i], set_member(elems[i], s) ? "OK": "FAIL", i==size - 1 ? "\n": ", ");
  }
  free(elems);
  /* Test remove operations*/
  if (nelims > 0) {
      printf("\n"
             "Removings elements: ");
      for (int i=0; i < nelims;i++) {
          printf("<%d> ", elim_elems[i]);
          s = set_elim(s, elim_elems[i]);
      }
      printf("DONE\n\n");
      printf("Resulting set with %u elements (%s): ", 
             set_cardinal(s), 
             set_is_empty(s) ? "empty": "not empty");
      set_dump(s);
      printf("\n");
  }
  s = set_destroy(s);
  return EXIT_SUCCESS;
}
