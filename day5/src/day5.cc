#include <array>
#include <cstdint>
#include <fstream>
#include <ios>
#include <iostream>
#include <istream>
#include <vector>

#include "custom_tree.h"

using std::cout;
using std::endl;

typedef std::vector<uint64_t> Seeds;

void read_seeds(Seeds& seeds, std::istream& file) {
  file.ignore(10, ' ');
  uint64_t num;
  seeds.reserve(60);

  while (true) {
    file >> num;
    if (file.eof() || file.fail()) break;
    seeds.push_back(num);
  }
  file.clear();
}

class MyMap {
  MyTreeMap map;

 public:
  void read(std::istream& file) {
    file.ignore(10000, ':');
    file.ignore(1, '\n');

    MyTreeEntry entry;
    file >> entry.dest;
    file >> entry.src;
    file >> entry.len;
    map.insert(entry);
  }
};

class MyMapList {
  std::array<MyMap, 7> maps;

 public:
  void read(std::istream& file) {
    for (auto& map : maps) {
      map.read(file);
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::ifstream file{"day5/example.txt"};

  Seeds seeds;
  read_seeds(seeds, file);

  MyMapList list;

  return 0;
}
