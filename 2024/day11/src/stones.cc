#include "stones.h"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>

uint32_t how_many_stones(uint64_t stone, uint16_t i) {
  if (i >= 25) return 1;
  if (stone == 0) return how_many_stones(1, i + 1);
  std::string stone_str = std::to_string(stone);

  if (stone_str.length() % 2 == 0) {
    std::string lower_half = stone_str.substr(0, stone_str.length() / 2);
    std::string upper_half =
        stone_str.substr(stone_str.length() / 2, stone_str.length());
    return how_many_stones(std::stoull(upper_half), i + 1) +
           how_many_stones(std::stoull(lower_half), i + 1);
  }
  return how_many_stones(stone * 2024, i + 1);
}

void read_stones(std::ifstream& input) {
  uint64_t in;
  uint32_t count = 0;
  while (!input.eof()) {
    input >> in;
    if (input.fail()) break;
    count += how_many_stones(in, 0);
  }
  std::cout << count << std::endl;
}
