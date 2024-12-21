#include "garden.h"

#include <cstddef>
#include <cstdint>

#include "region.h"

static RegionMap map;

static void what_to_do_with_a_single_kalap(StuffedMatrix& matrix, ssize_t i,
                                           ssize_t j) {
  char kalap = matrix[i][j];
  Region* reg = nullptr;
  uint16_t neighbour_count = 0;
  char balra = matrix[i][j - 1];
  if (matrix[i][j - 1] == kalap) {
    assert(i >= 0 && j > 0);
    reg = &map.get_region(i, j - 1);
    neighbour_count++;
  }
  if (matrix[i - 1][j] == kalap) {
    assert(i > 0 && j >= 0);
    reg = &map.get_region(i - 1, j);
    neighbour_count++;
  }
  if (reg == nullptr) {
    assert(i >= 0 && j >= 0);
    reg = &map.add_region();
    assert(reg->is_valid() == false);
    reg->create_new(kalap);
  }
  reg->inc_num();
  reg->add_border_num(4 - neighbour_count * 2);
  map.assign_region(i, j, reg);
}

void Garden::walk_garden() {
  for (size_t i = 0; i < matrix.size(); i++) {
    StuffedArray& row = matrix[i];
    for (size_t j = 0; j < row.size(); j++) {
      what_to_do_with_a_single_kalap(matrix, i, j);
    }
  }
}
uint64_t Garden::count_garden() {
  uint64_t count = 0;
  for (const Region& reg : map.get_regions()) {
    count += reg.count();
  }
  return count;
}
