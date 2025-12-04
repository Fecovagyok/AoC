#include <cstddef>
#include <cstdint>
#include <vector>

#include "aoc_reader.h"
#include "stuffed_matrix.h"

using MyMatrix = StuffedMatrix<unsigned char, '\0', 1>;

#define DIRECTIONS \
  X(0, 1)          \
  X(0, -1)         \
  X(1, 0)          \
  X(1, 1)          \
  X(1, -1)         \
  X(-1, 0)         \
  X(-1, 1)         \
  X(-1, -1)

int how_many_adjacents(MyMatrix& matrix, size_t i, size_t j) {
  int ret = 0;
#define X(vertical, horizontal)                          \
  if (matrix[i + (vertical)][j + (horizontal)] == '@') { \
    ret++;                                               \
  }
  DIRECTIONS
#undef X
  return ret;
}

struct MatrixIndex {
  size_t i;
  size_t j;
};

uint64_t process_rolls(MyMatrix& matrix) {
  uint64_t count = 0;
  static MatrixIndex scheduled_for_deletion[200 * 200];

  for (size_t i = 0; i < matrix.size(); i++) {
    auto row = matrix[i];
    for (size_t j = 0; j < row.size(); j++) {
      if (row[j] != '@') continue;
      int result = how_many_adjacents(matrix, i, j);
      if (result < 4) {
        scheduled_for_deletion[count] = {i, j};
        count++;
      }
    }
  }
  for (size_t i = 0; i < count; i++) {
    MatrixIndex idx = scheduled_for_deletion[i];
    matrix[idx.i][idx.j] = '.';
  }
  return count;
}

void process_rolls_multiple_times(MyMatrix& matrix) {
  uint64_t result_of_one;
  uint64_t sum = 0;
  while ((result_of_one = process_rolls(matrix)) != 0) {
    sum += result_of_one;
  }
  std::cout << sum << std::endl;
}

int main() {
  MyMatrix matrix;
  auto cb = [&matrix](std::string& line) { matrix.add_row(line); };
  AoCReader reader{cb, 1024, "input.txt"};
  reader.read();
  matrix.row_end();
  process_rolls_multiple_times(matrix);
  return 0;
}
