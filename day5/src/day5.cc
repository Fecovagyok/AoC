#include <algorithm>
#include <array>
#include <chrono>
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
  Intervals getIntervals(const Intervals& seed) const {
    return map.getAllInterval(seed);
  }
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

  Intervals findAllLocations(const Intervals& seeds) const {
    Intervals intervals = maps[0].getIntervals(seeds);
    for (size_t i = 1; i < maps.size(); i++) {
      intervals = maps[i].getIntervals(intervals);
    }
    return intervals;
  }

  void test(const Intervals& seeds) const {
    auto intervals = maps[0].getIntervals(seeds);
    for (const auto& soil : intervals) {
      std::cout << soil << "\n";
    }
  }
};

uint64_t find_lowest_seed(const Intervals& seeds, const MyMapList& list) {
  Intervals locations = list.findAllLocations(seeds);
  uint64_t min = -1;
  for (const Interval interval : locations) {
    std::cout << interval << "\n";
    min = std::min(min, interval.start);
  }
  return min;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::ifstream file{"day5/example.txt"};

  Intervals seeds;
  read_seeds(seeds, file);

  auto begin = std::chrono::high_resolution_clock::now();
  MyMapList list;
  list.read(file);

  uint64_t lowest = find_lowest_seed(seeds, list);
  auto end = std::chrono::high_resolution_clock::now();
  auto elapsed =
      std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin)
          .count() /
      1000000.0;

  std::cout << lowest << "\n"
            << "Took: " << elapsed << " milliseconds" << std::endl;

  return 0;
}
