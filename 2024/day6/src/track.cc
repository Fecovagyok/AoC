#include "track.h"

#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <type_traits>

MapMatrix::MapMatrix() : matrix{VEC_SIZE} {}

void MapMatrix::read_row(std::string& buf) {
  assert(read_rows < MAP_SIZE);
  for (size_t i = 0; i < buf.size(); i++) {
    map_row& row = matrix[read_rows + PADDING];
    assert(row.size() == buf.size());
    switch (buf[i]) {
      case '#':
        row[i] = Tile::obstacle;
        break;
      case '.':
        row[i] = Tile::empty;
        break;
      default:
        row[i] = Tile::empty;
        guard.look_up_by_char(buf[i], {read_rows + PADDING, i});
    }
  }
  read_rows++;
}

Tile MapMatrix::char_to_tile(char c) {
  switch (c) {
    case '#':
      return Tile::obstacle;
    default:
      return Tile::empty;
  }
}

void Guard::look_up_by_char(char c, track_position pos) {
  dir.from_char(c);
  this->pos = pos;
}

Guard::direction Guard::Direction::to_direction(char c) {
  switch (c) {
    case '^':
      return Up;
    case '>':
      return Right;
    case 'v':
      return Down;
    case '<':
      return Left;
    default:
      std::cerr << "Baj" << std::endl;
      std::exit(1);
  }
}

void Guard::Direction::turn_right() {
  std::underlying_type_t<direction> kalap =
      static_cast<std::underlying_type_t<direction>>(dir);
  dir = static_cast<direction>((kalap + 1) % 4);
}
