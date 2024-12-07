#include <aoc_reader.h>

#include <string>

int main() {
  Dataset matrix;
  auto cb = [&matrix](std::string& buf) { matrix.add_row(buf); };
  AoCReader reader{cb, 256, "./2024/day6/input2.txt"};
  reader.read();
  return 0;
}
