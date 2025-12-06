#include <aoc_reader.h>

int main() {
  auto cb = [](std::string&) {};
  AoCReader reader{cb, 8192, "2025/day6/input1.txt"};
  reader.read();
  return 0;
}
