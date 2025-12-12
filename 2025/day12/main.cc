#include <cassert>
#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

#include "aoc_reader.h"
#include "me_conversion.h"
#include "me_split.h"

struct Shape {
  char shape[3][3];
  unsigned int space_requirement = 0;
};

struct Place {
  uint32_t width;
  uint32_t length;
  std::vector<uint32_t> quotas;
  uint64_t space_requirement = 0;
  uint32_t shape_count = 0;
};

std::vector<Shape> shapes;
std::vector<Place> places;

struct Parsing {
  unsigned long current_idx = 0;
  Shape* current = nullptr;
  bool expect_shape = false;
  unsigned long shape_line = 0;
};

class PlaceMatrix {
  std::vector<char> array;

 public:
  PlaceMatrix(uint32_t row, uint32_t column) : array(column * row, '.') {
    array.reserve(column * row);
  }

  char& at(uint32_t row, uint32_t column) { return array.at(row * column); }
};

Shape rotate(Shape& to_be_rotated) {
  Shape shape = to_be_rotated;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      shape.shape[i][j] = to_be_rotated.shape[3 - 1 - j][i];
    }
  }
  return shape;
}

bool process_place(Place& place) {
  assert(place.quotas.size() == shapes.size());
  uint32_t count = place.quotas.at(2) / 2;
  uint32_t rem = place.shape_count - count * 2;
  if (rem * 9 <= place.length * place.width - count) {
    return true;
  }
  return false;
}

void process() {
  uint32_t count = 0;
  for (size_t i = 0; i < places.size(); i++) {
    Place& place = places[i];
    if (place.width * place.length < place.space_requirement) {
      continue;
    }
    if (place.length * place.width <= place.shape_count * 9) {
      count++;
      continue;
    }
    if (process_place(place)) {
      count++;
    }
  }
  std::cout << count << std::endl;
}

int main() {
  Parsing parsing;
  auto cb = [&parsing](std::string& line) {
    if (line == "") {
      parsing.expect_shape = false;
      return;
    }
    if (line.ends_with(':')) {
      parsing.current_idx = std::stoul(line.substr(0, line.size() - 1));
      assert(parsing.current_idx == shapes.size());
      parsing.current = &shapes.emplace_back();
      parsing.expect_shape = true;
      parsing.shape_line = 0;
      return;
    }

    if (parsing.expect_shape) {
      for (size_t i = 0; i < 3; i++) {
        parsing.current->shape[parsing.shape_line][i] = line[i];
        if (line[i] == '#') parsing.current->space_requirement++;
      }
      parsing.shape_line++;
      if (parsing.shape_line == 3) parsing.expect_shape = false;
      return;
    }

    std::vector<std::string_view> pieces = split(line);
    std::vector<std::string_view> dimensions =
        split(pieces[0].substr(0, pieces[0].size() - 1), 'x');

    Place& place = places.emplace_back();
    place.width = str_to_int32(dimensions[0]);
    place.length = str_to_int32(dimensions[1]);
    assert(pieces.size() == shapes.size() + 1);
    place.quotas.reserve(pieces.size() - 1);
    for (size_t i = 1; i < pieces.size(); i++) {
      uint32_t number = str_to_int32(pieces[i]);
      place.quotas.emplace_back(str_to_int32(pieces[i]));
      place.space_requirement +=
          shapes.at((place.quotas.size() - 1)).space_requirement * number;
      place.shape_count += number;
    }
  };
  AoCReader reader{cb, 512, "2025/day12/input.txt"};
  reader.read();
  process();
}
