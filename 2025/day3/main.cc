#include <aoc_reader.h>
#include <cstdint>

using IType = std::string::size_type;

constexpr uint64_t powers_of_ten[] = {
  1,
  10,
  100,
  1000,
  10000,
  100000,
  1000000,
  10000000,
  100000000,
  1000000000,
  10000000000,
  100000000000,
};

void process_digit(std::string& line, IType pos, unsigned char max[], signed int max_index[]) {
    for (IType i = max_index[pos - 1] + 1; i < line.length() - 11 + pos; i++) {
      unsigned char num = line[i];
      if(num > max[pos]) {
        max[pos]         = num;
        max_index[pos] = i;
      }
    }
}

uint64_t process_line(std::string& line) {
  unsigned char max_array[12] = {};
  signed int max_index_array[13] = {};
  max_index_array[0] = -1;

  uint64_t result = 0;

  for(IType i = 0; i < 12; i++) {
    process_digit(line, i, max_array, max_index_array + 1);
    result += static_cast<uint64_t>(max_array[i] - '0') * powers_of_ten[11 - i];
  }

  // unsigned char end_value[3] = {max_begin, max_end, '\0'};

  return result;
}

int main() {
  uint64_t sum = 0;
  auto cb = [&sum](std::string& line) {
    uint64_t big_num = process_line(line);
    sum += big_num;
  };
  AoCReader reader{cb, 1024, "input1.txt"};
  reader.read();
  std::cout << sum << std::endl;
  return 0;
}
