#include <aoc_reader.h>
#include <stuffed_matrix.h>

#include "dunno_yet.h"

extern StuffedMatrix<char> matrix;

int main() {
  auto cb = [](std::string& buf) { read_row(buf); };
  AoCReader reader{cb, 256, "./2024/day8/input2.txt"};
  reader.read();
  return 0;
}
