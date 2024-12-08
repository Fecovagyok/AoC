#include <aoc_reader.h>

#include "operator_stuff.h"

int main() {
  uint64_t sum = 0;
  auto cb = [&sum](std::string& buf) {
    Equation eq = read_equation(buf);
    sum += process_equation(eq);
  };
  AoCReader reader{cb, 256, "./2024/day7/input.txt"};
  reader.read();
  std::cout << sum << std::endl;
  std::cout << get_max() << std::endl;
  return 0;
}
