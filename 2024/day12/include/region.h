#pragma once
#include <array>
#include <cstdint>

class Region {
  bool valid = false;
  char type;
  uint32_t num;
  uint32_t border_num;

 public:
  bool is_valid() const { return valid; }
  void create_new(char kalap) {
    valid = true;
    type = kalap;
    num = 1;
    border_num = 4;
  }
};

class RegionMap {
  std::array<Region, 256> map;

 public:
  Region& operator[](char kalap) { return map[kalap]; }
};
