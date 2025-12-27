#include "aoc_reader.h"
#include "universe.h"

int main() {
  Universe universe;
  auto cb = [&universe](std::string& line) { universe.parse(line); };
  AoCReader reader{cb, 512, "2025/day11/input2.txt"};
  reader.read();
  universe.createInverseMap();
}
