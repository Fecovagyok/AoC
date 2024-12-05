#include "matrix.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define MATRIX_WIDTH 140
#define MATRIX_HEIGHT 140

#define XMAS "XMAS"
#define LEN_XMAS (sizeof(XMAS) - 1)

#define PADDING 4

#define MATRIX_ARRAY_HEIGHT (MATRIX_WIDTH + 2 * PADDING)
#define MATRIX_ARRAY_WIDTH (MATRIX_HEIGHT + 2 * PADDING)

static struct matrix_node internal_matrix[MATRIX_ARRAY_HEIGHT]
                                         [MATRIX_ARRAY_WIDTH];

static void read_row(FILE* input, size_t row) {
  assert(sizeof(struct matrix_node) == 1);

  fread(&(internal_matrix[row][PADDING]), 1, MATRIX_WIDTH, input);
  fgetc(input);
}

void read_matrix(FILE* input) {
  assert(sizeof(struct matrix_node) == 1);

  /* Create padding */
  memset(internal_matrix, ' ', sizeof(internal_matrix));

  for (size_t i = 0; i < MATRIX_HEIGHT; i++) {
    read_row(input, i + PADDING);
  }
}

int calc_for_one_direction(int32_t y_start, int32_t x_start, int32_t xe,
                           int32_t ye) {
  for (size_t i = 0; i < LEN_XMAS; i++) {
    if (internal_matrix[y_start + ye * i][x_start + xe * i].letter != XMAS[i])
      return 0;
  }
  return 1;
}

uint32_t count_for_one_point(size_t y, size_t x) {
  if (internal_matrix[y + 1][x + 1].letter != 'A') {
    return 0;
  }
  const char up_left = internal_matrix[y][x].letter;
  const char up_right = internal_matrix[y][x + 2].letter;
  const char down_left = internal_matrix[y + 2][x].letter;
  const char down_right = internal_matrix[y + 2][x + 2].letter;
  if (up_left == up_right && up_left == 'S' && down_left == down_right &&
      down_left == 'M') {
    return 1;
  } else if (up_left == up_right && up_left == 'M' && down_left == down_right &&
             down_left == 'S') {
    return 1;
  } else if (up_left == 'M' && up_right == 'S' && down_left == up_left &&
             up_right == down_right) {
    return 1;
  } else if (up_left == 'S' && up_right == 'M' && down_left == up_left &&
             up_right == down_right) {
    return 1;
  }
  return 0;
}

uint32_t count_matrix(void) {
  uint32_t sum = 0;
  for (size_t i = PADDING; i < MATRIX_HEIGHT + PADDING; i++) {
    for (size_t j = PADDING; j < MATRIX_WIDTH + PADDING; j++) {
      sum += count_for_one_point(i, j);
    }
  }
  return sum;
}
