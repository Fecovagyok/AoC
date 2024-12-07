#pragma once

#include <cstddef>
enum class Tile { out_of, empty, obstacle };

#include <string>
#include <vector>

using map_row = std::vector<Tile>;
using map_matrix = std::vector<map_row>;

struct track_position {
  size_t y, x;
};

class Guard {
  enum direction { Down, Left, Up, Right };
  class Direction {
    direction dir;
    direction to_direction(char c);

   public:
    void turn_right();
    void from_char(char c) { dir = to_direction(c); }
  };

  track_position pos;
  Direction dir;

 public:
  void look_up_by_char(char c, track_position pos);
};

class MapMatrix {
  size_t read_rows = 0;
  map_matrix matrix;
  Guard guard;

  Tile char_to_tile(char c);

 public:
  MapMatrix();
  void read_row(std::string& buf);
};
