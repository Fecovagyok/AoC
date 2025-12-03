#include <aoc_reader.h>
#include <cstdint>

unsigned char process_line(std::string& line) {
  using IType = std::string::size_type;
  unsigned char max_begin = '0';
  IType max_begin_index = 0;
  for(IType i= 0; i < line.length() - 1; i++) {
    unsigned char num = line[i];
    if(num > max_begin) {
      max_begin = num;
      max_begin_index = i;
    }
  }

  unsigned char max_end = '0';
  for(IType i = max_begin_index + 1; i < line.length(); i++) {
    unsigned char num = line[i];
    if(num >= max_end) {
      max_end = num;
    }
  }

  // unsigned char end_value[3] = {max_begin, max_end, '\0'};
  unsigned char result = (max_begin - '0') * 10 + max_end - '0';

  return result;
}

int main() {
  uint64_t sum = 0;
  auto cb = [&sum](std::string& line) {
    unsigned char num = process_line(line);
    uint64_t big_num = static_cast<uint64_t>(num);
    sum += big_num;
  };
  AoCReader reader{cb, 1024, "input.txt"};
  reader.read();
  std::cout << sum << std::endl;
  return 0;
}
