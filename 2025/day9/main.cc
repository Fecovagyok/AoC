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

  bool operator==(const Coord other) const {
    return other.coord[0] == coord[0] && other.coord[1] == coord[1];
  }
};

struct Tile {
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
  Tile() {}
  Tile(int32_t column, int32_t row) : coord{column, row} {}
  uint64_t calc_area(const Tile other) const {
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
  uint64_t operator*(const Tile other) const { return calc_area(other); }
  bool operator==(const Tile other) const { return other.coord == coord; }
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
  std::vector<Tile> tiles;
  std::unordered_map<Coord, Tile> map;

  void outlineShape(Tile prev, Tile current) {
    int different_axis;
    if (prev.coord[0] == current.coord[0]) {
      different_axis = 1;
    } else {
      different_axis = 0;
    }
    const Tile* bigger;
    const Tile* smaller;
    if (current.coord[different_axis] > prev.coord[different_axis]) {
      bigger = &current;
      smaller = &prev;
    } else {
      bigger = &prev;
      smaller = &current;
    }
    for (int32_t i = smaller->coord[different_axis];
         i <= bigger->coord[different_axis]; i++) {
      Tile rectangle = *smaller;
      rectangle.coord[different_axis] = i;
      map.emplace(rectangle);
    }
  }

  void parse(std::string& line) {
    std::vector<std::string_view> pieces = split(line, ',');
    assert(pieces.size() == 2);
    Tile current{static_cast<int32_t>(str_to_int32(pieces[0])),
                 static_cast<int32_t>(str_to_int32(pieces[1]))};
    if (tiles.size() > 0) {
      Tile& prev = tiles[tiles.size() - 1];
      outlineShape(prev, current);
    }
    tiles.push_back(current);
  }

  void finishOutlineShape() { outlineShape(tiles[tiles.size() - 1], tiles[0]); }

  bool isValidRectangleOnAxis(const Tile rec1, const Tile rec2, int axis) {
    const Tile* bigger;
    const Tile* smaller;
    if (rec1.coord[axis] > rec2.coord[axis]) {
      bigger = &rec1;
      smaller = &rec2;
    } else {
      bigger = &rec2;
      smaller = &rec1;
    }

    for (int32_t i = smaller->coord[axis]; i <= bigger->coord[axis]; i++) {
      Tile tangle = *smaller;
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

  bool isValidRectangle(const Tile tile1, const Tile tile2) {
    if (!isValidRectangleOnAxis(tile1, tile2, 0)) {
      return false;
    }

    if (!isValidRectangleOnAxis(tile1, tile2, 1)) {
      return false;
    }
    return true;
  }

  void solve() {
    uint64_t max = 0;
    for (size_t i = 0; i < tiles.size(); i++) {
      Tile& one = tiles[i];
      for (size_t j = i + 1; j < tiles.size(); j++) {
        Tile& other = tiles[j];
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
        Tile tangle{j, i};
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
  universe.tiles.reserve(500);
  auto cb = [&universe](std::string& line) { universe.parse(line); };
  AoCReader reader{cb, 128, "2025/day9/input1.txt"};
  reader.read();
  universe.finishOutlineShape();
  universe.printTiles();
  universe.solve();
}
