#include "aoc_reader.h"

int main() {
  int rot = 50;
  int count = 0;
  auto cb = [&rot, &count](std::string& line) {
    if (line.length() < 2) {
      std::cerr << "WTF: " << line << std::endl;
      return;
    }
    char rotDirection = line[0];
    int val = line.length() == 2 ? line[1] - '0'
                                 : (line[1] - '0') * 10 + line[2] - '0';
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
  AoCReader aoc_reader{cb, 159, "2025/day1/input1.txt"};
  aoc_reader.read();

  std::cout << count << std::endl;

  return 0;
}
