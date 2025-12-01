#include <climits>
#include <string>

#include "aoc_reader.h"

int main() {
  unsigned long rot = ((ULONG_MAX / 2) / 100) + 50;
  unsigned long count = 0;
  auto cb = [&rot, &count](std::string& line) {
    if (line.length() < 2) {
      std::cerr << "WTF: " << line << std::endl;
      return;
    }
    char rotDirection = line[0];
    const std::string substring = line.substr(1);
    unsigned long val = std::stoul(substring);
    if (rotDirection == 'L') {
      rot -= val;
    } else if (rotDirection == 'R') {
      rot += val;
    } else {
      std::cerr << "WTF2" << std::endl;
      return;
    }
    std::cout << line << ": " << rot << std::endl;
    if (rot % 100 == 0) {
      count++;
    }
  };
  AoCReader aoc_reader{cb, 5, "2025/day1/input1.txt"};
  aoc_reader.read();

  std::cout << count << std::endl;

  return 0;
}
