#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string_view>

#include "aoc_reader.h"
#include "me_conversion.h"
#include "me_split.h"

struct Rectangle {
  int32_t coord[2] = {};
  Rectangle() {}
  Rectangle(int32_t column, int32_t row) : coord{column, row} {}
  uint64_t calc_area(Rectangle other) const {
    uint64_t operand1 = std::abs(other.coord[0] - coord[0]) + 1;
    uint64_t operand2 = std::abs(other.coord[1] - coord[1]) + 1;
    return operand1 * operand2;
  }
  uint64_t operator*(Rectangle other) const { return calc_area(other); }
};

struct Universe {
  std::vector<Rectangle> rectangles;

  void parse(std::string& line) {
    std::vector<std::string_view> pieces = split(line, ',');
    assert(pieces.size() == 2);
    rectangles.emplace_back(str_to_int32(pieces[0]), str_to_int32(pieces[1]));
  }

  void solve() {
    uint64_t max = 0;
    for (size_t i = 0; i < rectangles.size(); i++) {
      Rectangle& one = rectangles[i];
      for (size_t j = i + 1; j < rectangles.size(); j++) {
        Rectangle& other = rectangles[j];
        uint64_t product = one * other;
        if (product > max) {
          max = product;
        }
      }
    }
    std::cout << max << std::endl;
  }
};

int main() {
  Universe universe;
  universe.rectangles.reserve(500);
  auto cb = [&universe](std::string& line) { universe.parse(line); };
  AoCReader reader{cb, 128, "2025/day9/input.txt"};
  reader.read();
  universe.solve();
}
