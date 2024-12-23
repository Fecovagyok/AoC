#include "dunno_yet.h"

#include <stuffed_matrix.h>

#include <cstddef>
#include <cstdint>
#include <unordered_set>
#include <utility>
#include <vector>

static StuffedMatrix matrix;

using MyCoordPoint = std::pair<ssize_t, ssize_t>;
using MyPoint = MyCoordPoint;

template <>
struct std::hash<MyPoint> {
  size_t operator()(const MyPoint& point) const noexcept {
    return point.first << 9 | point.second;
  }
};

inline static MyPoint operator-(const MyPoint& left, const MyPoint& right) {
  return MyPoint{left.first - right.first, left.second - right.second};
}

inline static MyPoint operator+(const MyPoint& left, const MyPoint& right) {
  return MyPoint{left.first + right.first, left.second + right.second};
}

using MyPointList = std::vector<MyPoint>;

static MyPointList freq_map[257];
static std::unordered_set<MyPoint> a_node_set;
static bool a_node_matrix[140][140];

void read_row(std::string& buf) {
  size_t row_num = matrix.size();
  matrix.add_row(buf);
  for (size_t j = 0; j < buf.size(); j++) {
    if (buf[j] == '.') continue;
    freq_map[static_cast<size_t>(buf[j])].emplace_back(row_num, j);
  }
}
void read_end() { matrix.row_end(); }

static void add_a_node(const MyPoint& a_node) {
  if (a_node.first < 0) return;
  if (a_node.second < 0) return;
  if (a_node.first >= static_cast<ssize_t>(matrix.size())) return;
  if (a_node.second >= static_cast<ssize_t>(matrix.size())) return;

  a_node_set.insert(a_node);
  a_node_matrix[a_node.first][a_node.second] = true;
}

static void check_freqs(const MyPointList& list) {
  for (size_t i = 0; i < list.size(); i++) {
    for (size_t j = i + 1; j < list.size(); j++) {
      MyPoint diff = list[j] - list[i];
      MyPoint a_node1 = list[i] - diff;
      MyPoint a_node2 = list[j] + diff;

      add_a_node(a_node1);
      add_a_node(a_node2);
    }
  }
}

uint64_t do_the_stuff() {
  for (const MyPointList& list : freq_map) {
    if (list.empty()) continue;
    check_freqs(list);
  }
  return a_node_set.size();
}

#include <iostream>
void print_debug() {
  size_t count = 0;
  for (size_t i = 0; i < matrix.size(); i++) {
    for (size_t j = 0; j < matrix.size(); j++) {
      if (a_node_matrix[i][j]) count++;
      std::cout << (a_node_matrix[i][j] ? '#' : '.');
    }
    std::cout << "\n";
  }
  std::cout << count << std::endl;
}
