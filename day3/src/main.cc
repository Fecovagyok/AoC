#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "aoc_reader.h"

class Matrix {
  std::vector<std::string> matrix;
  static constexpr size_t padding = 1;
  static constexpr size_t columns = 140;
  static constexpr size_t rows = 140;

 public:
  Matrix() {
    matrix.reserve(rows + 2 * padding);
    matrix.insert(matrix.begin(), std::string(columns + 2 * padding, ' '));
    matrix.insert(matrix.cend(), std::string(columns + 2 * padding, ' '));
  }

  void addRow(std::string& r) {
    if (r.size() != columns) {
      std::cerr << "Saaad" << std::endl;
      exit(EXIT_FAILURE);
    }
    std::string mine;
    mine.reserve(r.size() + padding * 2);
    mine = r;
    mine.insert(mine.cend(), ' ');
    mine.insert(mine.cbegin(), ' ');
    matrix.insert(matrix.end() - 1, std::move(mine));
  }
};

#define BUFF_SIZE 150

int main() {
  Matrix matrix;
  auto process_line = [&matrix](std::string& buf) { matrix.addRow(buf); };
  AoCReader reader{process_line, 150, "day3/input.txt"};
  return reader.read();
}
