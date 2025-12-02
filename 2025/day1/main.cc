#include <climits>
#include <string>

#include "aoc_reader.h"

unsigned long count_zeros(unsigned long& rot, std::string& line) {
  if (line.length() < 2) {
    std::cerr << "WTF: " << line << std::endl;
    return 0;
  }
  char rotDirection = line[0];
  const std::string substring = line.substr(1);
  unsigned long val = std::stoul(substring);
  unsigned long howMany100s = val / 100;
  bool hundredOverFlow;
  if (rotDirection == 'L') {
    hundredOverFlow = rot % 100 - 1 < val % 100;
    rot -= val;
  } else if (rotDirection == 'R') {
    hundredOverFlow = rot % 100 + val % 100 >= 100;
    rot += val;
  } else {
    std::cerr << "WTF2" << std::endl;
    return 0;
  }
  return hundredOverFlow ? 1 + howMany100s : howMany100s;
}

int main() {
  unsigned long rot = (((ULONG_MAX / 2) / 100) * 100) + 50;
  unsigned long count = 0;
  auto cb = [&rot, &count](std::string& line) {
    count += count_zeros(rot, line);
  };
  AoCReader aoc_reader{cb, 5, "2025/day1/input.txt"};
  aoc_reader.read();

  std::cout << count << std::endl;

  return 0;
}
