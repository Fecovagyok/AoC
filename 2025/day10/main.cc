#include <aoc_reader.h>

#include <cctype>
#include <cstddef>

#include "machine_stuff.h"

int main() {
  auto cb = [](std::string& line) { parse_that(line); };
  AoCReader reader{cb, 1024, "2025/day10/input.txt"};
  reader.read();
  solve_all_machines();
  return 0;
}
