#ifdef __WIN32__
#include <windows.h>
#define MEASURING_STUFF
#endif

#include <cstdint>
#include <format>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <string_view>

using fInt = uint64_t;

struct Range {
  fInt start;
  fInt end;
};

bool process_number(fInt num) {
  auto num_str = std::to_string(num);
  std::string_view num_view{num_str};
  using IType = std::string::size_type;
  for (IType i = 1; i - 1 < num_str.length() / 2; i++) {
    if (num_view.length() % i != 0) {
      continue;
    }
    std::string_view pattern_view = num_view.substr(0, i);
    std::string pattern_format = std::format("^(?:{})+$", pattern_view);
    std::regex pattern{pattern_format};
    std::smatch match;
    bool matched = std::regex_match(num_str, match, pattern);
    if (matched) {
      return true;
    }
  }
  return false;
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
  std::ifstream input{"2025/day2/input.txt"};
  if (!input.is_open()) {
    std::cerr << "HMmm" << std::endl;
    return 1;
  }

#ifdef MEASURING_STUFF
  HANDLE hTread = GetCurrentThread();
  ULONG64 startCycles = 0;
  ULONG64 endCycles = 0;
  QueryThreadCycleTime(hTread, &startCycles);
#endif

  int ret = process_input(input);

#ifdef MEASURING_STUFF
  QueryThreadCycleTime(hTread, &endCycles);
  std::cout << "Measured: " << (endCycles - startCycles) << std::endl;
#endif

  return ret;
}
