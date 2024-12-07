#include "game.h"

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <unordered_set>

#include "track.h"

// Custom specialization of std::hash can be injected in namespace std.
template <>
struct std::hash<track_position> {
  size_t operator()(track_position pos) const noexcept {
    return pos.y << 8 | pos.x;
  }
};

template <>
struct std::hash<Guard> {
  size_t operator()(Guard pos) const noexcept {
    return pos.pos.y << 10 | pos.pos.x << 2 | pos.dir.get_dir();
  }
};

int is_guard_looped(MapMatrix& matrix) {
  std::unordered_set<Guard> touched;
  touched.insert(matrix.get_guard());

  while (true) {
    Tile new_tile = matrix.guard_next_tile();
    if (new_tile == Tile::obstacle) {
      matrix.turn_guard_right();
    } else if (new_tile == Tile::out_of) {
      break;
    } else {
      matrix.move_forward();
      Guard pos = matrix.get_guard();
      if (touched.find(pos) == touched.end()) {
        touched.insert(pos);
      } else {
        return 1;
      }
    }
  }
  return 0;
}

uint32_t run_games(MapMatrix& base) {
  uint32_t sum = 0;
  for (size_t i = PADDING; i < base.matrix.size() - PADDING; i++) {
    for (size_t j = 0; j < base.matrix[i].size(); j++) {
      if (base.matrix[i][j] == Tile::obstacle ||
          track_position{i, j} == base.guard_current_pos())
        continue;
      assert(base.matrix[i][j] == Tile::empty);
      base.matrix[i][j] = Tile::obstacle;
      base.save_guard_pos();
      sum += is_guard_looped(base);
      base.load_guard_pos();
      base.matrix[i][j] = Tile::empty;
    }
  }
  return sum;
}
