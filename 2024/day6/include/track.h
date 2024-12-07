#pragma once

#include <corecrt.h>

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

struct track_pos_delta {
  ssize_t y, x;
};

struct track_position {
  size_t y, x;

  void operator+(track_pos_delta other) {
    y = static_cast<ssize_t>(y) + other.y;
    x = static_cast<ssize_t>(x) + other.x;
  }

  bool operator==(track_position other) const {
    return y == other.y && x == other.x;
  }
};

class Guard {
  enum direction { Down, Left, Up, Right };
  class Direction {
    direction dir;
    direction to_direction(char c);

   public:
    void turn_right();
    void from_char(char c) { dir = to_direction(c); }
    track_pos_delta to_delta_pos();
  };

  // Padding-aware

 public:
  track_position pos;
  Direction dir;
  void look_up_by_char(char c, track_position pos);
  track_position next_tile() {
    track_position pos = this->pos;
    pos + dir.to_delta_pos();
    return pos;
  }
  void move_forward() { pos + dir.to_delta_pos(); }
};

class MapMatrix {
  size_t read_rows = 0;
  Guard guard;

  Tile char_to_tile(char c);
  track_position saved_pos;

 public:
  MapMatrix();
  map_matrix matrix;
  void read_row(std::string& buf);
  Tile guard_next_tile() {
    track_position next_pos = guard.next_tile();
    return matrix[next_pos.y][next_pos.x];
  }
  void turn_guard_right() { guard.dir.turn_right(); }
  void move_forward() { guard.move_forward(); }
  track_position guard_current_pos() { return guard.pos; }
  void save_guard_pos() { saved_pos = guard.pos; }
  void load_guard_pos() { guard.pos = saved_pos; }
};
