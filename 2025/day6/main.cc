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

constexpr int lines = 3;
constexpr char ADDITION = '+';
constexpr char MULTIP = '*';

std::string pre_everything[lines];

char operations[1000];

void read_operand(int operand, std::string& line) {
  pre_everything[operand] = line;
  return;
}

void process_operands() {
  using IType = std::string::size_type;
  for (IType column = 0; true; column++) {
    bool numbers_started[lines] = {};
    uint32_t column_ends[lines];
    for (int row = 0; row < lines; row++) {
      char val = pre_everything[row][column];
      if (numbers_started[row]) {
        if (isspace(val)) {
          // Next number
          numbers_started[row] = false;
        } else {
        }
      } else {
        if (!isspace(val)) {
          numbers_started[row] = true;
        }
      }
    }
  }
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

void process_everything() {
  uint64_t grand_total = 0;
  for (int i = 0; everyting[i]._operator != Operation::_operator::NOTHING;
       i++) {
    uint64_t op_result =
        everyting[i]._operator == Operation::_operator::ADDITION ? 0 : 1;
    for (int count = 0; true; count++) {
      Operation& ops = everyting[i];
      uint32_t num_result = 0;
#define X(num, mul)                                                         \
  if (count < ops.operand##num.len && ops.operand##num.buf[count] != ' ') { \
    uint32_t val =                                                          \
        ops.operand##num.buf[ops.operand##num.len - count - 1] - '0';       \
    num_result = 10 * num_result + val;                                     \
  }
      OPERANDS
#undef X
      if (num_result == 0) {
        break;
      }
      if (everyting[i]._operator == Operation::_operator::ADDITION) {
        op_result += num_result;
      } else {
        op_result *= num_result;
      }
    }
    grand_total += op_result;
  }
  std::cout << grand_total << std::endl;
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
  AoCReader reader{cb, 4096, "2025/day6/input1.txt"};
  reader.read();
  process_operands();
  process_everything();
  return 0;
}
