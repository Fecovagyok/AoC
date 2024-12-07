#include <cstdint>

#include "aoc_reader.h"
#include "pagin.h"
#include "rulin.h"

int main() {
  bool readin_rules = true;
  uint32_t sum = 0;
  auto cb = [&readin_rules, &sum](std::string& buf) {
    if (buf.empty()) {
      readin_rules = false;
      return;
    }
    if (readin_rules) {
      read_rules(buf);
    } else {
      sum += read_pages(buf);
    }
  };
  AoCReader reader{cb, 250, "./2024/day5/input.txt"};
  reader.read();
  std::cout << sum << std::endl;

  return 0;
}
