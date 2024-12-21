#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>

class Region {
  bool valid = false;
  char type = 0;
  uint64_t num = 0;
  uint64_t border_num = 0;

 public:
  void inc_num() { num++; }
  void add_border_num(uint16_t i) { border_num += i; }
  bool is_valid() const { return valid; }
  void create_new(char kalap) {
    valid = true;
    type = kalap;
  }
  uint64_t count() { return num * border_num; }
};

class RegionMap {
  std::vector<Region> regionPool;
  std::vector<std::vector<Region*>> map{140,
                                        std::vector<Region*>{140, nullptr}};

 public:
  Region& get_region(size_t i, size_t j) { return *map[i][j]; }
  Region& add_region() { return regionPool.emplace_back(); }
  void assign_region(size_t i, size_t j, Region* reg) { map[i][j] = reg; }
  size_t regions_size() { return regionPool.size(); }
  Region& get_region(size_t i) { return regionPool[i]; }
};
