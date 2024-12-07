#include <aoc_reader.h>

#include "operator_stuff.h"

int main() {
  auto cb = [](std::string& buf) { read_equation(buf); };
  AoCReader reader{cb, 256, "./2024/day7/input2.txt"};
  reader.read();
  return 0;
}
