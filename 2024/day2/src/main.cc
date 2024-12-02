#include <aoc_reader.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <ostream>
#include <sstream>
#include <vector>

using Matrix = std::vector<std::vector<uint32_t>>;

enum class DescendType { Descending, Ascending, Either };

bool process_mutated_row(const std::vector<uint32_t>& row) {
  DescendType type = DescendType::Either;
  for (size_t i = 1; i < row.size(); i++) {
    uint32_t in_prev = row[i - 1];
    uint32_t in = row[i];
    if (in_prev == in) {
      /* Unsafe */
      return false;
    }
    switch (type) {
      case DescendType::Either:
        type = in_prev > in ? DescendType::Descending : DescendType::Ascending;
        break;
      case DescendType::Descending:
        if (in_prev < in) {
          /* Unsafe */
          return false;
        }
        break;
      case DescendType::Ascending:
        if (in_prev > in) {
          /*Unsafe*/
          return false;
        }
    }
    uint32_t bigger = in_prev > in ? in_prev : in;
    uint32_t smaller = in_prev > in ? in : in_prev;
    if (bigger - smaller > 3) {
      /*Unsafe*/
      return false;
    }
    in_prev = in;
  }
  return true;
}

std::ostream& operator<<(std::ostream& os, const std::vector<uint32_t>& vec) {
  os << vec[0];
  for (size_t i = 1; i < vec.size(); i++) {
    os << " " << vec[i];
  }
  return os;
}

bool process_row(std::vector<uint32_t>& row, std::istream& input) {
  if (input.eof() || input.fail()) {
    std::cerr << "Baj2" << std::endl;
    std::exit(1);
  }
  while (true) {
    uint32_t in;
    input >> in;
    if (input.fail()) {
      std::cerr << "Baj" << std::endl;
      std::exit(1);
    }
    row.push_back(in);
    if (input.eof()) break;
  }
  if (process_mutated_row(row)) {
    return true;
  }

  for (size_t i = 0; i < row.size(); i++) {
    std::vector<uint32_t> cut_row = row;
    cut_row.erase(cut_row.begin() + i);
    if (process_mutated_row(cut_row)) {
      std::cout << row << " -- Safe" << " Cut: " << cut_row << "\n";
      return true;
    }
  }
  return false;
}

int main() {
  Matrix matrix;
  matrix.reserve(1000);
  uint32_t count = 0;
  auto cb = [&matrix, &count](std::string& buf) {
    if (buf.empty()) return;
    std::istringstream input{buf};
    std::vector<uint32_t> row;
    if (process_row(row, input)) {
      count++;
    }
    if (row.size() != 0) matrix.push_back(std::move(row));
  };
  AoCReader reader{cb, 260, "2024/day2/input.txt"};
  reader.read();

  std::cout << count << std::endl;
  return 0;
}
