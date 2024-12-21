#pragma once
#include <array>
#include <cstdint>

class Region {
  bool valid = false;
  char type = 0;
  uint32_t num = 0;
  uint32_t border_num = 0;

 public:
  void inc_num() { num++; }
  void add_border_num(uint16_t i) { border_num += i; }
  bool is_valid() const { return valid; }
  void create_new(char kalap) {
    valid = true;
    type = kalap;
  }
};

class RegionMap {
  std::array<Region, 256> map;

 public:
  Region& operator[](char kalap) { return map[kalap]; }
};
