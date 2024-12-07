#pragma once

#include <cstddef>
enum class Tile { out_of, empty, obstacle };

#include <string>
#include <vector>

#define MAP_SIZE 10
#define PADDING 1
#define VEC_SIZE (MAP_SIZE + 2 * PADDING)

// I don't need vector for this but nvm
class map_row {
  std::vector<Tile> tiles;
  Tile& get_item(size_t i) { return tiles[i + PADDING]; }

 public:
  map_row() : tiles{VEC_SIZE, Tile::out_of} {}
  size_t size() const { return tiles.size() - 2 * PADDING; }
  Tile& operator[](size_t i) { return get_item(i); }
};

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

  // Padding-aware
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
