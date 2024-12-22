#pragma once

#include <vector>

#define PADDING_CHAR '\0'

template <typename T = char, T PADDING = PADDING_CHAR, size_t PADDING_SIZE = 1>
class StuffedArray {
  std::vector<T> kalap;

 public:
  explicit StuffedArray(size_t pref_size = 140) { kalap.reserve(pref_size); }
  T& at(ssize_t idx) { return kalap[idx + 1]; }
  T& operator[](ssize_t idx) { return at(idx); }
  size_t size() const { return kalap.size() - 2 * PADDING; }
  template <class Iter>
  typename std::vector<T>::iterator insert(
      typename std::vector<T>::const_iterator pos, Iter beg, Iter end) {
    return kalap.insert(pos, beg, end);
  }
  typename std::vector<T>::const_iterator cend() { return kalap.cend(); }
};

template <typename T = char, T PADDING = PADDING_CHAR, size_t PADDING_SIZE = 1>
class StuffedMatrix {
  std::vector<StuffedArray<T, PADDING, PADDING_SIZE>> kalap;

 public:
  explicit StuffedMatrix(size_t pref_size = 140) { kalap.reserve(pref_size); }
  StuffedArray<T, PADDING, PADDING_SIZE>& at(ssize_t idx) {
    return kalap[idx + 1];
  }
  StuffedArray<T, PADDING, PADDING_SIZE>& operator[](ssize_t idx) {
    return at(idx);
  }
  size_t size() const { return kalap.size() - 2 * PADDING; }

  template <class TypeCont>
  void add_row(const TypeCont& in) {
    StuffedArray<T, PADDING, PADDING_SIZE>& elem = kalap.emplace_back();
    elem.insert(elem.cend(), in.cbegin(), in.cend());
  }
};
