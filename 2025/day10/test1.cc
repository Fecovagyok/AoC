#include <aoc_reader.h>

#include "machine_stuff.h"

void test_input1() {
  Machine& machine = machine_at(0);
  machine.press_multiple_buttons(0, 1, 2);
}

void test_input2() {
  Machine& machine = machine_at(0);
  machine.press_multiple_buttons(4, 5);
}

int main() {
  auto cb = [](std::string& line) { parse_that(line); };
  AoCReader reader{cb, 1024, "2025/day10/input1.txt"};
  reader.read();
  test_input2();
  machine_at(0).test_machine();
  return 0;
}
