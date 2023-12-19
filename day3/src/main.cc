#include <cctype>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include "aoc_reader.h"

static constexpr size_t padding = 1;

static bool is_symbol(char c) {
  return c != '.' && ((c < '0' && c > ' ') || (c < 'A' && c > '9'));
}

static bool contains_symbol(const std::string_view str) {
  for (size_t i = 0; i < str.size(); i++) {
    if (is_symbol(str[i])) {
      return true;
    }
  }
  return false;
}

class MyString {
  std::string str;

 public:
  MyString() : str{} {}

  MyString(const std::string& s) {
    str.reserve(s.size());
    str = s;
    str.insert(str.cend(), '.');
    str.insert(str.cbegin(), '.');
  }
  MyString(size_t n, char fill) : str(n, fill) {}

  size_t size() const { return str.size() - 2; }

  char operator[](size_t idx) const { return str[idx + 1]; }

  const std::string_view substr(size_t start, size_t n) const {
    return std::string_view{str.c_str() + 1 + start, n};
  }

  const std::string_view extendedRow(size_t column, size_t n) const {
    return substr(column - 1, n + 2);
  }

  const std::string_view toStringView() const {
    return std::string_view{str.c_str() + 1, str.size() - 2};
  }
};

class Matrix {
  std::vector<MyString> matrix;
  static constexpr size_t columns = 140;
  static constexpr size_t rows = 140;

 public:
  Matrix() {
    matrix.reserve(rows + 2 * padding);
    matrix.insert(matrix.begin(), MyString(columns + 2 * padding, '.'));
    matrix.insert(matrix.cend(), MyString(columns + 2 * padding, '.'));
  }

  size_t size() const { return matrix.size() - 2; }
  const MyString& operator[](size_t idx) const { return matrix[idx + 1]; }
  const MyString& at(size_t idx) const { return operator[](idx); }

  void addRow(std::string& r) {
    if (r.size() != columns) {
      std::cerr << "Saaad" << std::endl;
      exit(EXIT_FAILURE);
    }
    MyString mine{r};
    matrix.insert(matrix.end() - 1, std::move(mine));
  }

  bool isPart(size_t row, size_t column, size_t n) const {
    // Check the two possible rows separately
    auto first_row = at(row - 1).extendedRow(column, n);
    auto last_row = at(row + 1).extendedRow(column, n);

    // And the remaining block separately
    char first_block = at(row)[column - 1];
    char last_block = at(row)[column + n];

    if (is_symbol(first_block) || is_symbol(last_block) ||
        contains_symbol(first_row) || contains_symbol(last_row))
      return true;
    return false;
  }
};

uint64_t myToInt(const MyString& str, size_t i, size_t* size) {
  uint64_t num = 0;
  size_t start_i = i;
  for (size_t my_i = i; my_i < str.size() && std::isdigit(str[my_i]); my_i++) {
    num = num * 10 + str[my_i] - '0';
    i++;
  }
  *size = i - start_i;
  return num;
}

uint64_t sumParts(const Matrix& matrix) {
  uint64_t sum = 0;
  for (size_t i = 0; i < matrix.size(); i++) {
    for (size_t j = 0; j < matrix[i].size(); j++) {
      if (std::isdigit(matrix[i][j])) {
        size_t numsize;
        size_t res = myToInt(matrix[i], j, &numsize);
        if (matrix.isPart(i, j, numsize)) {
          sum += res;
        }
        j += numsize;
      }
    }
  }
  return sum;
}

#define BUFF_SIZE 150

int main() {
  Matrix matrix;
  auto process_line = [&matrix](std::string& buf) { matrix.addRow(buf); };
  AoCReader reader{process_line, 150, "day3/input.txt"};
  int result = reader.read();
  if (result < 0) return result;

  std::cout << "Sum of parts: " << sumParts(matrix) << std::endl;
  return 0;
}
