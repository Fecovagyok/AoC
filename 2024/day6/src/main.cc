#include <aoc_reader.h>

#include "game.h"
#include "track.h"

int main() {
  MapMatrix matrix;
  auto cb = [&matrix](std::string& buf) { matrix.read_row(buf); };
  AoCReader reader{cb, 256, "./2024/day6/input2.txt"};
  reader.read();
  uint32_t count = run_game(matrix);
  std::cout << count << std::endl;
  return 0;
}
