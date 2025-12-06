#include <aoc_reader.h>

#include <array>
#include <cctype>
#include <cstdint>
#include <sstream>
#include <string>

struct Operation {
  uint64_t operand1;
  uint64_t operand2;
  uint64_t operand3;
  uint64_t operand4;
  enum class _operator { NOTHING, ADDITION, MULTIPLICATION };
  _operator _operator;
};

using MyEverything = std::array<Operation, 4096>;

void process_operand(MyEverything& everything, uint64_t Operation::* operand,
                     std::string& line) {
  std::istringstream is{line};
  int count = 0;
  while (!is.eof()) {
    uint64_t num;
    is >> num;
    if (is.bad() || is.fail()) {
      break;
    }
    everything[count++].*operand = num;
  }
}

Operation convert_operation(const Operation& op) {}

void process_operation(MyEverything& everything, std::string& line) {
  using IType = std::string::size_type;
  int count = 0;
  for (IType i = 0; i < line.size(); i++) {
    if (line[i] == '+') {
      everything[count++]._operator = Operation::_operator::ADDITION;
    }
    if (line[i] == '*') {
      everything[count++]._operator = Operation::_operator::MULTIPLICATION;
    }
  }
}

void process_everything(MyEverything& old, MyEverything& current) {
  for (int i = 0; old[i]._operator != Operation::_operator::NOTHING; i++) {
    unsigned char nums[64];
    Operation& old_op = old[i];
    current[i]._operator = old_op._operator;
    uint64_t most_sig = old_op.operand1;
    for (uint64_t j = 0; most_sig > 0; j++) {
      uint64_t num = most_sig % 10;
      most_sig /= 10;
    }
  }
}

void process_all_operations(MyEverything& everything) {
  uint64_t result = 0;
  for (int i = 0; everything[i]._operator != Operation::_operator::NOTHING;
       i++) {
    if (everything[i]._operator == Operation::_operator::ADDITION) {
      result += everything[i].operand1 + everything[i].operand2 +
                everything[i].operand3 + everything[i].operand4;
    } else {
      result += everything[i].operand1 * everything[i].operand2 *
                everything[i].operand3 * everything[i].operand4;
    }
  }
  std::cout << result << std::endl;
}

int main() {
  MyEverything pre_everything = {};
  int cnt = 0;
  auto cb = [&pre_everything, &cnt](std::string& line) {
    switch (cnt) {
      case 0:
        process_operand(pre_everything, &Operation::operand1, line);
        break;
      case 1:
        process_operand(pre_everything, &Operation::operand2, line);
        break;
      case 2:
        process_operand(pre_everything, &Operation::operand3, line);
      case 3:
        process_operand(pre_everything, &Operation::operand4, line);
      default:
        process_operation(pre_everything, line);
        break;
    }
    cnt++;
  };
  AoCReader reader{cb, 4096, "2025/day6/input.txt"};
  reader.read();
  MyEverything everything = {};
  process_all_operations(pre_everything);
  return 0;
}
