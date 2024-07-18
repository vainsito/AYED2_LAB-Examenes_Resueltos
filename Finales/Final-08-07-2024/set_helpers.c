#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "set.h"

set set_from_file(const char *filepath) {
    FILE *file = NULL;
    set output=set_empty();
    file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    while (!feof(file)) {
        int elem;
        int res = fscanf(file," %d ", &elem);
        if (res != 1) {
            fprintf(stderr, "Invalid set.\n");
            exit(EXIT_FAILURE);
        }
        output = set_add(output, elem);
    }
    fclose(file);
    assert(output != NULL);
    return output;
}
