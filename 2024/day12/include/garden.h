#pragma once

#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>

#define MATRIX_SIZE 10
#define PADDING 1
#define ARRAY_SIZE (MATRIX_SIZE + 2 * PADDING)
#define PADDING_CHAR '\0'

class StuffedArray {
  std::array<char, ARRAY_SIZE> kalap{PADDING_CHAR};

 public:
  char& at(ssize_t idx) { return kalap[idx + 1]; }
  char& operator[](ssize_t idx) { return at(idx); }
  size_t size() const { return kalap.size() - 2 * PADDING; }
};

class StuffedMatrix {
  std::array<StuffedArray, ARRAY_SIZE> kalap;
  size_t curr_size = 0;

 public:
  StuffedArray& at(ssize_t idx) { return kalap[idx + 1]; }
  StuffedArray& operator[](ssize_t idx) { return at(idx); }
  size_t size() const { return kalap.size() - 2 * PADDING; }

  void add_row(std::string& in) {
    for (size_t i = 0; i < at(curr_size).size(); i++) {
      at(curr_size)[i] = in[i];
    }
    curr_size++;
  }

  void rows_end() { assert(curr_size == MATRIX_SIZE); }
};

class Garden {
  StuffedMatrix& matrix;

 public:
  Garden(StuffedMatrix& matrix) : matrix{matrix} {}

  void walk_garden();
  uint64_t count_garden();
};
