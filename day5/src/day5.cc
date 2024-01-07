#include <array>
#include <cstdint>
#include <fstream>
#include <ios>
#include <iostream>
#include <istream>
#include <ostream>
#include <vector>

#include "custom_tree.h"

typedef std::vector<Seed> Seeds;

void read_seeds(Seeds& seeds, std::istream& file) {
  file.ignore(10, ' ');
  Seed seed;
  seeds.reserve(60);

  while (true) {
    file >> seed.seed_start;
    file >> seed.seed_len;
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
};

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
};

uint64_t find_lowest_seed(const Seeds& seeds, const MyMapList& list) {
  uint64_t min = -1;
  for (const auto& seed : seeds) {
    for (uint64_t i = seed.seed_start; i < seed.seed_start + seed.seed_len;
         i++) {
      uint64_t loc = list.getLocation(i);
      if (loc < min) {
        min = loc;
      }
    }
  }
  return min;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::ifstream file{"day5/input.txt"};

  Seeds seeds;
  read_seeds(seeds, file);

  MyMapList list;
  list.read(file);

  std::cout << find_lowest_seed(seeds, list) << std::endl;

  return 0;
}
