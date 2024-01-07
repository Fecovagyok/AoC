#include <cstdint>
#include <istream>

#include "common.h"

struct MyTreeEntry {
  uint64_t dest = 0;
  uint64_t src = 0;
  uint64_t len = 0;
};

class MyTreeMap {
  MyTreeMap* left = nullptr;
  MyTreeEntry entry;
  MyTreeMap* right = nullptr;

  size_t elements = 0;

 public:
  friend MyTreeMap* recur_insert(MyTreeMap* root, const MyTreeEntry& entry);
  uint64_t getSrc() const { return entry.src; }
  void insert(const MyTreeEntry& num);
  uint64_t get(uint64_t num) const;
  void read(std::istream& file);
  uint64_t get_min(const Seed& seed);

  ~MyTreeMap();
};
