#include "stones.h"

#include <pthread.h>

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <utility>

#include "calculator.h"
#include "unordered_map"

using my_pair = std::pair<uint64_t, uint16_t>;

template <>
struct std::hash<my_pair> {
  std::size_t operator()(const my_pair& s) const noexcept {
    return (static_cast<uint64_t>(s.second) << (64 - 7)) ^ s.first;
  }
};

static std::unordered_map<my_pair, uint64_t> cache_map;

uint64_t how_many_stones(uint64_t stone, uint16_t i) {
  if (i >= 75) return 1;
  if (stone == 0) return how_many_stones(1, i + 1);

  auto found = cache_map.find(std::make_pair(stone, 75 - i));
  if (found != cache_map.end()) {
    return found->second;
  }

  char num_str[22];
  uint16_t len = my_to_string(num_str, stone);

  if (len % 2 == 0) {
    return how_many_stones(my_to_long(num_str, len / 2), i + 1) +
           how_many_stones(my_to_long(num_str + len / 2, len / 2), i + 1);
  }
  uint64_t counted = how_many_stones(stone * 2024, i + 1);
  cache_map[std::make_pair(stone, 75 - i)] = counted;
  return counted;
}

void read_stones(std::ifstream& input) {
  uint64_t in;
  uint64_t count = 0;
  while (!input.eof()) {
    input >> in;
    if (input.fail()) break;
    count += how_many_stones(in, 0);
  }
  std::cout << count << std::endl;
}
