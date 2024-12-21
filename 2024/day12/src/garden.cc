#include "garden.h"

#include <array>
#include <cstddef>
#include <cstdint>

#include "region.h"

static RegionMap map;

static void what_to_do_with_a_single_kalap(StuffedMatrix& matrix, size_t i,
                                           size_t j) {
  char kalap = matrix[i][j];
  Region* reg = nullptr;
  uint16_t neighbour_count = 0;
  if (matrix[i][j - 1] == kalap) {
    reg = &map[matrix[i][j - 1]];
    neighbour_count++;
  }
  if (matrix[i - 1][j] == kalap) {
    reg = &map[matrix[i - 1][j]];
    neighbour_count++;
  }
  if (reg == nullptr) {
    reg = &map[kalap];
    assert(reg->is_valid() == false);
    reg->create_new(kalap);
  }
  reg->inc_num();
  reg->add_border_num(4 - neighbour_count);
}

void Garden::walk_garden() {
  for (size_t i = 0; i < matrix.size(); i++) {
    StuffedArray& row = matrix[i];
    for (size_t j = 0; j < row.size(); j++) {
      what_to_do_with_a_single_kalap(matrix, i, j);
    }
  }
}
