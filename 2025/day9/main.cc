#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string_view>
#include <unordered_set>

#include "aoc_reader.h"
#include "me_conversion.h"
#include "me_split.h"

struct Coord {
  int32_t coord[2] = {};
  Coord() {}
  Coord(int32_t column, int32_t row) : coord{column, row} {}
  template <typename T>
  int32_t& operator[](T idx) {
    return coord[idx];
  }

  template <typename T>
  const int32_t& operator[](T idx) const {
    return coord[idx];
  }

  bool operator==(const Coord other) {
    return other.coord[0] == coord[0] && other.coord[1] == coord[1];
  }
};

struct Rectangle {
#define DIRECTIONS \
  X(Up, -1, 0)     \
  X(Down, 1, 0)    \
  X(Right, 0, 1)   \
  X(Left, 0, -1)

#define X(name, row_m, column_m) name,
  enum class Direction : uint8_t { DIRECTIONS };
#undef X

  Coord coord;
  Direction dir = Direction::Up;
  Direction prev_dir = Direction::Up;
  Rectangle() {}
  Rectangle(int32_t column, int32_t row) : coord{column, row} {}
  uint64_t calc_area(Rectangle other) const {
    uint64_t operand1 = std::abs(other.coord[0] - coord[0]) + 1;
    uint64_t operand2 = std::abs(other.coord[1] - coord[1]) + 1;
    return operand1 * operand2;
  }
  void move(Direction direction) {
    switch (direction) {
#define X(name, row_m, column_m) \
  case Direction::name:          \
    coord[0] += column_m;        \
    coord[1] += row_m;           \
    break;
      DIRECTIONS
#undef X
    }
  }

  void move_forward() { move(dir); }
  void move_backward() { move(prev_dir); }
  uint64_t operator*(Rectangle other) const { return calc_area(other); }
  bool operator==(const Rectangle other) const { return other.coord == coord; }
};

namespace std {
template <>
struct hash<Coord> {
  uint64_t operator()(const Coord rectangle) const noexcept {
    return (static_cast<uint64_t>(rectangle.coord[0]) << 32) +
           rectangle.coord[1];
  }
};
}  // namespace std

struct Universe {
  std::vector<Rectangle> rectangles;
  std::unordered_map<Coord, Rectangle> map;

  void fillShape() {
    Rectangle f_current = rectangles[0];
    Rectangle b_current = rectangles[0];
    f_current.move_forward();
    b_current.move_backward();
    while (f_current != rectangles[0] || b_current != rectangles[0]) {
      auto f_current_found = map.find(f_current.coord);
      while (f_current_found == map.end() ||
             f_current_found->second.dir == f_current.dir) {
        f_current.move_forward();
      }

      auto b_current_found = map.find(b_current.coord);
      while (b_current_found == map.end() ||
             b_current_found->second.prev_dir == b_current.prev_dir) {
        b_current.move_backward();
      }
      // Rectangle& prev =
      //     i == 0 ? rectangles[rectangles.size() - 1] : rectangles[i - 1];
      rectangles[i].dir
    }
  }

  void outlineShape(Rectangle prev, Rectangle current) {
    int different_axis;
    if (prev.coord[0] == current.coord[0]) {
      different_axis = 1;
    } else {
      different_axis = 0;
    }
    const Rectangle* bigger;
    const Rectangle* smaller;
    if (current.coord[different_axis] > prev.coord[different_axis]) {
      bigger = &current;
      smaller = &prev;
    } else {
      bigger = &prev;
      smaller = &current;
    }
    for (int32_t i = smaller->coord[different_axis];
         i <= bigger->coord[different_axis]; i++) {
      Rectangle rectangle = *smaller;
      rectangle.coord[different_axis] = i;
      map.emplace(rectangle);
    }
  }

  void parse(std::string& line) {
    std::vector<std::string_view> pieces = split(line, ',');
    assert(pieces.size() == 2);
    Rectangle current{static_cast<int32_t>(str_to_int32(pieces[0])),
                      static_cast<int32_t>(str_to_int32(pieces[1]))};
    // if (rectangles.size() > 0) {
    //   Rectangle& prev = rectangles[rectangles.size() - 1];
    //   outlineShape(prev, current);
    // }
    rectangles.push_back(current);
  }

  void finishOutlineShape() {
    outlineShape(rectangles[rectangles.size() - 1], rectangles[0]);
  }

  bool isValidRectangleOnAxis(const Rectangle rec1, const Rectangle rec2,
                              int axis) {
    const Rectangle* bigger;
    const Rectangle* smaller;
    if (rec1.coord[axis] > rec2.coord[axis]) {
      bigger = &rec1;
      smaller = &rec2;
    } else {
      bigger = &rec2;
      smaller = &rec1;
    }

    for (int32_t i = smaller->coord[axis]; i <= bigger->coord[axis]; i++) {
      Rectangle tangle = *smaller;
      tangle.coord[axis] = i;
      if (map.contains(tangle.coord)) {
        return false;
      }
      tangle = *bigger;
      tangle.coord[axis] = i;
      if (map.contains(tangle.coord)) {
        return false;
      }
    }
    return true;
  }

  bool isValidRectangle(const Rectangle rec1, const Rectangle rec2) {
    if (!isValidRectangleOnAxis(rec1, rec2, 0)) {
      return false;
    }

    if (!isValidRectangleOnAxis(rec1, rec2, 1)) {
      return false;
    }
    return true;
  }

  void solve() {
    uint64_t max = 0;
    for (size_t i = 0; i < rectangles.size(); i++) {
      Rectangle& one = rectangles[i];
      for (size_t j = i + 1; j < rectangles.size(); j++) {
        Rectangle& other = rectangles[j];
        if (!isValidRectangle(one, other)) {
          continue;
        }
        uint64_t product = one * other;
        if (product > max) {
          max = product;
        }
      }
    }
    std::cout << max << std::endl;
  }

  void printTiles() {
    for (int32_t i = 0; i < 16; i++) {
      for (int32_t j = 0; j < 16; j++) {
        Rectangle tangle{j, i};
        if (map.find(tangle) == map.end()) {
          std::cout << '.';
        } else {
          std::cout << '#';
        }
      }
      std::cout << '\n';
    }
  }
};

int main() {
  Universe universe;
  universe.rectangles.reserve(500);
  auto cb = [&universe](std::string& line) { universe.parse(line); };
  AoCReader reader{cb, 128, "2025/day9/input1.txt"};
  reader.read();
  universe.finishOutlineShape();
  universe.printTiles();
  universe.solve();
}
