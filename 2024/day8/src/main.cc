#include <aoc_reader.h>
#include <stuffed_matrix.h>

#include "dunno_yet.h"

int main() {
  auto cb = [](std::string& buf) { read_row(buf); };
  AoCReader reader{cb, 256, "./2024/day8/input.txt", read_end};
  reader.read();
  std::cout << do_the_stuff() << std::endl;
  // print_debug();
  return 0;
}
