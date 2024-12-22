#pragma once

#include <vector>

#define PADDING_CHAR '\0'

template <typename T = char, T PADDING = PADDING_CHAR, size_t PADDING_SIZE = 1>
class StuffedArray {
  std::vector<T> kalap;

 public:
  explicit StuffedArray(size_t pref_size = 200) { kalap.reserve(pref_size); }
  explicit StuffedArray(size_t count, const T& val) : kalap(count, val) {}
  T& at(ssize_t idx) { return kalap[idx + PADDING_SIZE]; }
  T& operator[](ssize_t idx) { return at(idx); }
  size_t size() const { return kalap.size() - 2 * PADDING_SIZE; }
  template <class Iter>
  void insert_back(Iter beg, Iter end) {
    kalap.push_back(PADDING);
    kalap.insert(kalap.cend(), beg, end);
    kalap.push_back(PADDING);
  }
  typename std::vector<T>::const_iterator cend() { return kalap.cend(); }
};

template <typename T = char, T PADDING = PADDING_CHAR, size_t PADDING_SIZE = 1>
class StuffedMatrix {
  std::vector<StuffedArray<T, PADDING, PADDING_SIZE>> kalap;

 public:
  explicit StuffedMatrix(size_t pref_size = 200) { kalap.reserve(pref_size); }
  StuffedArray<T, PADDING, PADDING_SIZE>& at(ssize_t idx) {
    return kalap[idx + PADDING_SIZE];
  }
  StuffedArray<T, PADDING, PADDING_SIZE>& operator[](ssize_t idx) {
    return at(idx);
  }
  size_t size() const { return kalap.size() - 2 * PADDING_SIZE; }

  template <class TypeCont>
  void add_row(const TypeCont& in) {
    StuffedArray<T, PADDING, PADDING_SIZE>& elem = kalap.emplace_back();
    elem.insert_back(in.cbegin(), in.cend());
  }

  void row_end() {
    size_t num_of = kalap.size();
    kalap.emplace(kalap.begin(), num_of + 2 * PADDING_SIZE, PADDING);
    kalap.emplace_back(num_of + 2 * PADDING_SIZE, PADDING);
  }
};
