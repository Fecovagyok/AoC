#include <cassert>
#include <cstdint>
#include <exception>
#include <iostream>
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

template <typename T>
auto str_to_int(const std::string_view str) -> T {
  using MyType = std::string_view::size_type;
  T ret = 0;
  if (str.size() > 20) {
    std::cerr << "Problematic: " << str << std::endl;
    throw std::runtime_error("You should only give me numbers");
  }
  for (MyType i = 0; i < str.size(); i++) {
    MyType rev = str.size() - i - 1;
    assert(powersOfTen[i] < (static_cast<T>(0) - static_cast<T>(1)));
    ret += static_cast<T>(str[rev] - '0') * static_cast<T>(powersOfTen[i]);
  }
  return ret;
}

uint64_t str_to_int64(const std::string_view str) {
  return str_to_int<uint64_t>(str);
}

uint32_t str_to_int32(const std::string_view str) {
  return str_to_int<uint32_t>(str);
}
