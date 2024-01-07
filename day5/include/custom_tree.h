#include <cstdint>
#include <istream>
#include <vector>

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
  friend void recur_get_intervals(MyTreeMap* root, std::vector<Interval>& intervals,
                                  const Interval& interval);
  friend MyTreeMap* recur_insert(MyTreeMap* root, const MyTreeEntry& entry);
  uint64_t getSrc() const { return entry.src; }
  void insert(const MyTreeEntry& num);
  uint64_t get(uint64_t num) const;
  void read(std::istream& file);
  std::vector<Interval> get_min(const Interval& seed);

  ~MyTreeMap();
};
