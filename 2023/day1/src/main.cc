#include <cctype>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

#define BUFF_SIZE 150

static bool own_cmp(const std::string& lhs, size_t start, const char* rhs,
                    size_t count) {
  for (size_t i = 0; i < count; i++) {
    if (i < lhs.size() && lhs[start+i] != rhs[i]) {
      return false;
    }
  }
  return true;
}

int16_t mr_characters(const std::string& str, size_t start) {
  static const char* map[] = {"one", "two",   "three", "four", "five",
                              "six", "seven", "eight", "nine"};
  static const unsigned long long sizes[] = {3, 3, 5, 4, 4, 3, 5, 5, 4};
  for (size_t i = 0; i < 9; i++) {
    if (own_cmp(str, start, map[i], sizes[i])) return i + 1;
  }
  return -1;
}

uint16_t mr_logic(const std::string& buf) {
  char first = 10 + '0';
  char last;
  for (size_t i = 0; i < buf.size(); i++) {
    char c = buf[i];
    if (std::isdigit(c)) {
      if (first > '0' + 9) first = c;
      last = c;
    } else {
      int16_t res = mr_characters(buf, i);
      if (res >= 0) {
        if (first > '0' + 9) first = res + '0';
        last = res + '0';
      }
    }
  }
  if (10 == first) {
    throw "_---__";
  }
  uint16_t tru_num = (first - '0') * 10 + last - '0';
  return tru_num;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::ifstream input{"input.txt"};
  if (input.fail()) {
    std::cout << "Balfasz" << std::endl;
    return 1;
  }

  std::string buf;
  buf.reserve(BUFF_SIZE);
  uint32_t osszeg = 0;
  while (true) {
    std::getline(input, buf);
    if (input.eof()) {
      break;
    }
    if (input.fail()) {
      std::cout << "Balfasz" << std::endl;
      return 1;
    }
    osszeg += mr_logic(buf);
  }
  std::cout << osszeg << std::endl;

  return 0;
}
