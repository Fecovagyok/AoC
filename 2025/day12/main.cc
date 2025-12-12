#include <cassert>
#include <cstddef>
#include <cstdint>
#include <format>
#include <string>
#include <string_view>
#include <vector>

#include "aoc_reader.h"
#include "me_conversion.h"
#include "me_split.h"

struct Shape {
  char shape[3][3];
};

struct Place {
  uint32_t width;
  uint32_t length;
  std::vector<uint32_t> quotas;
};

std::vector<Shape> shapes;
std::vector<Place> places;

struct Parsing {
  unsigned long current_idx = 0;
  Shape* current = nullptr;
  bool expect_shape = false;
  unsigned long shape_line = 0;
};

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
      place.quotas.emplace_back(str_to_int32(pieces[i]));
    }

    std::cout << line << std::endl;
  };
  AoCReader reader{cb, 512, "2025/day12/input1.txt"};
  reader.read();
}
