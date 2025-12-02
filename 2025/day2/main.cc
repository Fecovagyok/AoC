#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

using fInt = unsigned long;

struct Range {
  fInt start;
  fInt end;
};

bool process_number(fInt num) {
  auto num_str = std::to_string(num);
  std::string_view num_view{num_str};
  if (num_view.length() % 2 == 1) {
    return false;
  }
  return num_view.substr(0, num_view.length() / 2) ==
         num_view.substr(num_view.length() / 2);
}

uint64_t process_range(Range range) {
  uint64_t sum = 0;
  for (; range.start <= range.end; range.start++) {
    if (process_number(range.start)) {
      sum += range.start;
    }
  }
  return sum;
}

int process_input(std::ifstream& input) {
  fInt start, end;
  char expected;
  uint64_t sum = 0;
  while (!input.eof() && !input.fail()) {
    input >> start >> expected >> end;
    if (expected != '-') {
      std::cerr << "Hmm2" << std::endl;
      return -1;
    }
    if (!input.eof()) {
      input >> expected;
      if (!input.eof() && expected != ',') {
        std::cerr << "Hmm3: " << expected << std::endl;
        return -1;
      }
    }
    sum += process_range({start, end});
  }
  std::cout << sum << std::endl;
  return 0;
}

int main() {
  std::ifstream input{"2025/day2/input1.txt"};
  if (!input.is_open()) {
    std::cerr << "HMmm" << std::endl;
    return 1;
  }
  return process_input(input);
}
