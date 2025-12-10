#include <cstdint>
#include <exception>
#include <stdexcept>
#include <string_view>

#include "me_conversion.h"

static uint64_t powersOfTen[] = {1ULL,
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

uint64_t str_to_int(const std::string_view str) {
  using MyType = std::string_view::size_type;
  uint64_t ret = 0;
  if (str.size() > sizeof(powersOfTen) / sizeof(uint64_t))
    throw std::runtime_error("You should only give me numbers");
  for (MyType i = 0; i < str.size(); i++) {
    MyType rev = str.size() - i - 1;
    ret += static_cast<uint64_t>(str[rev] - '0') * powersOfTen[i];
  }
  return ret;
}
