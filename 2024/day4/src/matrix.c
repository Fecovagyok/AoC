#include "matrix.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define MATRIX_WIDTH 140
#define MATRIX_HEIGHT 140

#define PADDING 4

#define MATRIX_ARRAY_HEIGHT (MATRIX_WIDTH + 2 * PADDING)
#define MATRIX_ARRAY_WIDTH (MATRIX_HEIGHT + 2 * PADDING)

static struct matrix_node internal_matrix[MATRIX_ARRAY_HEIGHT]
                                         [MATRIX_ARRAY_WIDTH];

static void read_row(FILE* input, size_t row) {
  assert(sizeof(struct matrix_node) == 1);

  fread(&(internal_matrix[row][PADDING]), 1, 140, input);
  fseek(input, 1, SEEK_CUR);
}

void read_matrix(FILE* input) {
  assert(sizeof(struct matrix_node) == 1);
  /* Create padding */
  memset(internal_matrix, ' ', sizeof(internal_matrix));

  for (size_t i = 0; i < MATRIX_HEIGHT; i++) {
    read_row(input, i + PADDING);
  }
}
