#include <algorithm>
#include <array>
#include <cstdint>
#include <fstream>
#include <ios>
#include <iostream>
#include <istream>
#include <ostream>
#include <vector>

#include "custom_tree.h"

using std::cout;
using std::endl;

struct Seed {
  uint64_t seed;
  uint64_t location = 0;
};

typedef std::vector<Seed> Seeds;

void read_seeds(Seeds& seeds, std::istream& file) {
  file.ignore(10, ' ');
  Seed seed;
  seeds.reserve(60);

  while (true) {
    file >> seed.seed;
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

  uint64_t getLocation(Seed& seed) {
    uint64_t seed_val = seed.seed;
    for (const auto& map : maps) {
      seed_val = map.get(seed_val);
    }
    seed.location = seed_val;
    return seed_val;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::ifstream file{"day5/example.txt"};

  Seeds seeds;
  read_seeds(seeds, file);

  MyMapList list;
  list.read(file);

  for (auto& seed : seeds) list.getLocation(seed);

  std::cout << std::min_element(seeds.cbegin(), seeds.cend(),
                                [](const Seed first, const Seed second) {
                                  return first.location < second.location;
                                })
                   ->location
            << std::endl;

  return 0;
}
