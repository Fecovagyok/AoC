#include "garden.h"

#include <cstddef>
#include <cstdint>
#include <functional>
#include <unordered_set>

#include "region.h"

using my_pair = std::pair<ssize_t, ssize_t>;

template <>
struct std::hash<my_pair> {
  size_t operator()(const my_pair e) const { return (e.first << 9) | e.second; }
};

static std::unordered_set<my_pair> node_set;

static RegionMap map;

struct direction {
  int16_t y;
  int16_t x;
};

static const direction all_directions[] = {
    {-1, 0},  // up
    {0, -1},  // left
    {0, 1},   // right
    {1, 0},   // down
};

static Region* find_all_those_crooked_ones(StuffedMatrix& matrix, ssize_t i,
                                           ssize_t j, char kalap) {
  if (matrix[i][j] == PADDING_CHAR) return nullptr;
  if (matrix[i][j] != kalap) return nullptr;
  Region* reg = map.get_region(i, j);
  if (reg != nullptr) {
    return reg;
  }
  if (node_set.find(std::make_pair(i, j)) != node_set.end()) {
    return nullptr;
  }
  node_set.emplace(i, j);
  for (const direction& dir : all_directions) {
    ssize_t new_i = i + dir.y;
    ssize_t new_j = j + dir.x;
    Region* reg = find_all_those_crooked_ones(matrix, new_i, new_j, kalap);
    if (reg != nullptr) {
      map.assign_region(i, j, reg);
      return reg;
    }
  }
  return nullptr;
}

static void what_to_do_with_a_single_kalap(StuffedMatrix& matrix, ssize_t i,
                                           ssize_t j) {
  char kalap = matrix[i][j];

  Region* reg = map.get_region(i, j);
  if (reg == nullptr) {
    node_set.clear();
    reg = find_all_those_crooked_ones(matrix, i, j, kalap);
  }
  if (reg == nullptr) {
    assert(i >= 0 && j >= 0);
    reg = &map.add_region();
    assert(reg->is_valid() == false);
    reg->create_new(kalap);
    map.assign_region(i, j, reg);
  }
  int16_t neighbour_count = 0;
  for (const direction& dir : all_directions) {
    if (matrix[i + dir.y][j + dir.x] == kalap) {
      neighbour_count++;
    }
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
uint64_t Garden::count_garden() {
  uint64_t count = 0;
  for (const Region& reg : map.get_regions()) {
    count += reg.count();
  }
  return count;
}
