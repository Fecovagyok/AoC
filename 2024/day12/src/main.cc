#include "aoc_reader.h"
#include "garden.h"

int main() {
  StuffedMatrix matrix;
  auto cb = [&matrix](std::string& buf) { matrix.add_row(buf); };
  AoCReader reader{cb, 256, "./2024/day12/input.txt"};
  reader.read();
  matrix.rows_end();
  Garden garden{matrix};

  garden.walk_garden();
  std::cout << garden.count_garden() << std::endl;
}
