#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

int main(void) {
  FILE* input = fopen("./2024/day4/input.txt", "rt");
  if (input == NULL) {
    fprintf(stderr, "Baj\n");
    return 1;
  }

  read_matrix(input);
  uint32_t count = count_matrix();
  printf("%u\n", count);
}
