#include <aoc_reader.h>

#include <algorithm>
#include <cmath>
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

bool comparator(const Range& lhs, const Range& rhs) {
  return lhs.start < rhs.start;
}

void process_ranges() {
  uint64_t max = ranges[0].end;
  uint64_t count = ranges[0].end - ranges[0].start + 1;
  for (size_t i = 1; i < ranges.size(); i++) {
    uint64_t overlap = 0;
    if (max >= ranges[i].start) {
      overlap = std::min(max, ranges[i].end) - ranges[i].start + 1;
    }
    if (ranges[i].end > max) {
      max = ranges[i].end;
    }
    count += (ranges[i].end - ranges[i].start + 1) - overlap;
  }
  std::cout << count << std::endl;
}

int main() {
  bool ranges_reading = true;
  std::regex pattern{"(\\d+)-(\\d+)"};
  std::smatch match;

  auto cb = [&ranges_reading, &pattern, &match](std::string& line) {
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
    }
  };
  AoCReader reader{cb, 200, "2025/day5/input.txt"};
  reader.read();
  process_ranges();
  return 0;
}
