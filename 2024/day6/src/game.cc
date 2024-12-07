#include "game.h"

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

uint32_t run_game(MapMatrix& matrix) {
  std::unordered_set<track_position> touched;
  touched.insert(matrix.guard_current_pos());
  while (true) {
    Tile new_tile = matrix.guard_next_tile();
    if (new_tile == Tile::obstacle) {
      matrix.turn_guard_right();
    } else if (new_tile == Tile::out_of) {
      break;
    } else {
      matrix.move_forward();
      touched.insert(matrix.guard_current_pos());
    }
  }
  return touched.size();
}
