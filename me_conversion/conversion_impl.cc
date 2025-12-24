#include <cassert>
#include <cstdint>
#include <limits>
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
  for (MyType i = 0; i < str.size(); i++) {
    MyType rev = str.size() - i - 1;
    assert(powersOfTen[i] < (static_cast<T>(0) - static_cast<T>(1)));
    assert(str[rev] >= '0' && str[rev] <= '9');
    ret += static_cast<T>(str[rev] - '0') * static_cast<T>(powersOfTen[i]);
  }
  return ret;
}

uint64_t str_to_int64(const std::string_view str) {
  if (std::numeric_limits<uint64_t>::digits10 < str.size()) {
    throw std::runtime_error("Number too big");
  }
  return str_to_int<uint64_t>(str);
}

uint32_t str_to_int32(const std::string_view str) {
  if (std::numeric_limits<uint32_t>::digits10 < str.size()) {
    throw std::runtime_error("Number too big");
  }
  return str_to_int<uint32_t>(str);
}
