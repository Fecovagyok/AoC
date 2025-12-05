#include <aoc_reader.h>

#include <algorithm>
#include <cstdint>
#include <regex>
#include <string>

struct Range {
  uint64_t start;
  uint64_t end;
};

std::vector<Range> ranges;

void add_range(uint64_t start, uint64_t end) {
  ranges.emplace_back(start, end);
}

bool is_inside(uint64_t ing_id) {
  for (size_t i = 0; i < ranges.size(); i++) {
    if (ing_id >= ranges[i].start && ing_id <= ranges[i].end) {
      return true;
    }
  }
  return false;
}

int main() {
  bool ranges_reading = true;
  std::regex pattern{"(\\d+)-(\\d+)"};
  std::smatch match;
  uint64_t count = 0;

  auto cb = [&ranges_reading, &pattern, &match, &count](std::string& line) {
    if (line.empty()) {
      ranges_reading = false;
      return;
    }
    if (ranges_reading) {
      bool success = std::regex_match(line, match, pattern);
      if (!success) {
        std::cerr << "WTF" << std::endl;
        return;
      }
      if (match.size() != 3) {
        std::cerr << "WTF2" << std::endl;
        return;
      }

      static_assert(sizeof(unsigned long long) == 8);
      uint64_t start = std::stoull(match[1]);
      uint64_t end = std::stoull(match[2]);
      add_range(start, end);

    } else {
      uint64_t ing_id = std::stoull(line);
      if (is_inside(ing_id)) {
        count++;
      }
    }
  };
  AoCReader reader{cb, 200, "2025/day5/input.txt"};
  reader.read();
  std::cout << count << std::endl;
  return 0;
}
