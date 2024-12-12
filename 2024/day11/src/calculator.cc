#include "calculator.h"

#include <array>
#include <cstddef>
#include <cstdint>

std::array powers_of_ten = {1ULL,
                            10ULL,
                            100ULL,
                            1000ULL,
                            10000ULL,
                            100000ULL,
                            1000000ULL,
                            10000000ULL,
                            100000000ULL,
                            1000000000ULL,
                            10000000000ULL,
                            100000000000ULL,
                            1000000000000ULL,
                            10000000000000ULL,
                            100000000000000ULL,
                            1000000000000000ULL,
                            10000000000000000ULL,
                            100000000000000000ULL,
                            1000000000000000000ULL,
                            10000000000000000000ULL};

uint32_t my_num_len(uint64_t num) {
  uint16_t max;
  for (max = 0; max < powers_of_ten.size(); max++) {
    if (num < powers_of_ten[max]) {
      break;
    }
  }
  return max;
}

uint16_t my_to_string(char* dst, uint64_t num) {
  uint32_t length = my_num_len(num);
  uint16_t i = 0;
  for (; length > 0; length--) {
    uint64_t digit = num / powers_of_ten[length - 1];
    dst[i] = '0' + static_cast<char>(digit);
    num = num - digit * powers_of_ten[length - 1];
    i++;
  }
  dst[i] = '\0';
  return i;
}

uint64_t my_to_long(char* str, uint16_t len) {
  uint64_t ret = 0;
  for (uint16_t i = 0; i < len; i++) {
    ret = ret * 10 + (str[i] - '0');
  }
  return ret;
}
