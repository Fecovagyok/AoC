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
  size_t i = ranges.size() / 2;
  size_t start = 0;
  size_t after_end = ranges.size();
  while (true) {
    if (after_end - start <= 1) {
      return ing_id >= ranges.at(i).start && ing_id <= ranges.at(i).end;
    }
    if (ing_id < ranges.at(i).start) {
      after_end = i;
      i = (after_end + start) / 2;
      continue;
    }
    if (ing_id <= ranges.at(i).end) {
      return true;
    }
    start = i + 1;
    i = (after_end + start) / 2;
  }
}

bool comparator(const Range& lhs, const Range& rhs) {
  return lhs.start < rhs.start;
}

int main() {
  bool ranges_reading = true;
  std::regex pattern{"(\\d+)-(\\d+)"};
  std::smatch match;
  uint64_t count = 0;

  auto cb = [&ranges_reading, &pattern, &match, &count](std::string& line) {
    if (line.empty()) {
      ranges_reading = false;
      std::sort(ranges.begin(), ranges.end(), comparator);
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
