#include <cstdint>
#include <sstream>
#include <string>
#include <unordered_set>

#include "aoc_reader.h"

uint16_t calcPoints(uint16_t count) {
  if (count == 0) return 0;

  uint16_t hatvany = 1;
  for (uint16_t i = 0; i < count - 1; i++) {
    hatvany = hatvany * 2;
  }
  return hatvany;
}

int main() {
  uint64_t points = 0;
  auto process_line = [&points](std::string& buf) {
    std::istringstream ss{buf};
    ss.ignore(buf.size(), ':');
    ss.ignore(buf.size(), ' ');
    std::unordered_set<uint16_t> winners(9);
    for (uint8_t i = 0; i < 9; i++) {
      uint16_t in;
      ss >> in;
      winners.insert(in);
    }
    ss.ignore(3);
    uint16_t count = 0;
    for (uint16_t i = 0; i < 25; i++) {
      uint16_t in;
      ss >> in;
      if (winners.find(in) != winners.cend()) {
        count++;
      }
    }
    points += calcPoints(count);
  };

  AoCReader reader{process_line, 270, "day4/input.txt"};
  reader.read();
}
