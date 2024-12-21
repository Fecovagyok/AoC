#pragma once
#include <cstddef>
#include <cstdint>
#include <list>
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
  uint64_t count() const { return num * border_num; }
};

class RegionMap {
  std::list<Region> regionPool;
  std::vector<std::vector<Region*>> map{140,
                                        std::vector<Region*>{140, nullptr}};

 public:
  Region& get_region(size_t i, size_t j) { return *map[i][j]; }
  Region& add_region() { return regionPool.emplace_back(); }
  void assign_region(size_t i, size_t j, Region* reg) { map[i][j] = reg; }
  const std::list<Region>& get_regions() const { return regionPool; }
};
