#include <array>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <ios>
#include <iostream>
#include <istream>
#include <ostream>
#include <vector>

#include "custom_tree.h"

typedef std::vector<Interval> Intervals;

void read_seeds(Intervals& seeds, std::istream& file) {
  file.ignore(10, ' ');
  Interval seed;
  seeds.reserve(60);

  while (true) {
    file >> seed.start;
    file >> seed.len;
    if (file.eof() || file.fail()) break;
    seeds.push_back(seed);
  }
  file.clear();
}

class MyMap {
  MyTreeMap map;

 public:
  void read(std::istream& file) {
    file.ignore(10000, ':');
    file.ignore(1, '\n');

    while (file.peek() != '\n' && !file.eof() && !file.fail()) {
      map.read(file);
      file.ignore(1, '\n');
    }
  }

 public:
  uint64_t get(uint64_t num) const { return map.get(num); }
  Intervals get_min(const Interval& seed) const { return map.get_min(seed); }
};

inline std::ostream& operator<<(std::ostream& os, const Interval& interval) {
  return os << "Start: " << interval.start << " "
            << "Len: " << interval.len;
}

class MyMapList {
  std::array<MyMap, 7> maps{};

 public:
  void read(std::istream& file) {
    for (auto& map : maps) {
      map.read(file);
    }
  }

  uint64_t getLocation(uint64_t seed) const {
    uint64_t seed_val = seed;
    for (const auto& map : maps) {
      seed_val = map.get(seed_val);
    }
    return seed_val;
  }

  void test(const Intervals& seeds) const {
    for (size_t i = 0; i < seeds.size(); i++) {
      Intervals result = maps[0].get_min(seeds[i]);
      for (const auto& interval : result) {
        std::cout << interval << "\n";
      }
    }
  }
};

uint64_t find_lowest_seed(const Intervals& seeds, const MyMapList& list) {
  list.test(seeds);
  return 0;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::ifstream file{"day5/example.txt"};

  Intervals seeds;
  read_seeds(seeds, file);

  MyMapList list;
  list.read(file);

  std::cout << find_lowest_seed(seeds, list) << std::endl;

  return 0;
}
