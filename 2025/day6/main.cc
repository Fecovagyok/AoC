#include <aoc_reader.h>

#include <array>
#include <cctype>
#include <cstdint>
#include <sstream>
#include <string>

#define OPERANDS \
  /*X(1, 1000)*/ \
  X(2, 100)      \
  X(3, 10)       \
  X(4, 1)

struct MyChar {
  int len;
  char buf[15];
};

constexpr int lines = 4;

std::string pre_everything[lines];

char operations[1000 + 1];

void read_operand(int operand, std::string& line) {
  pre_everything[operand] = line;
  return;
}

void process_operands() {
  using IType = std::string::size_type;
  uint64_t grand_total = 0;
  uint64_t local_total;
  int op_count = 0;
  if (operations[0] == '+') {
    local_total = 0;
  } else {
    local_total = 1;
  }
  for (IType column = 0; column < pre_everything[0].size(); column++) {
    uint32_t parsed_vertical_num = 0;
    for (int row = 0; row < lines; row++) {
      if (!isspace(pre_everything[row][column])) {
        unsigned char val = pre_everything[row][column];
        parsed_vertical_num =
            10 * parsed_vertical_num + static_cast<uint32_t>(val - '0');
      }
    }
    if (parsed_vertical_num == 0) {
      char operation = operations[++op_count];
      grand_total += local_total;
      if (operation == '+') {
        local_total = 0;
      } else if (operation == '*') {
        local_total = 1;
      }
    } else {
      char operation = operations[op_count];
      if (operation == '+') {
        local_total += parsed_vertical_num;
      } else {
        local_total *= parsed_vertical_num;
      }
    }
  }
  std::cout << grand_total + local_total << std::endl;
}

void process_operation(std::string& line) {
  using IType = std::string::size_type;
  int count = 0;
  for (IType i = 0; i < line.size(); i++) {
    if (!isspace(line[i])) {
      operations[count++] = line[i];
    }
  }
}

int main() {
  int cnt = 0;
  auto cb = [&cnt](std::string& line) {
    if (cnt < lines) {
      read_operand(cnt, line);
    } else {
      process_operation(line);
    }
    cnt++;
  };
  AoCReader reader{cb, 4096, "2025/day6/input.txt"};
  reader.read();
  process_operands();
  return 0;
}
