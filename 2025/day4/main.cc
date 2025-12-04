#include <cstddef>

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

void process_rolls(MyMatrix& matrix) {
  uint64_t count = 0;
  for (size_t i = 0; i < matrix.size(); i++) {
    auto row = matrix[i];
    for (size_t j = 0; j < row.size(); j++) {
      if (row[j] != '@') continue;
      int result = how_many_adjacents(matrix, i, j);
      if (result < 4) {
        count++;
      }
    }
  }
  std::cout << count << std::endl;
}

int main() {
  MyMatrix matrix;
  auto cb = [&matrix](std::string& line) { matrix.add_row(line); };
  AoCReader reader{cb, 1024, "input.txt"};
  reader.read();
  matrix.row_end();
  process_rolls(matrix);
  return 0;
}
