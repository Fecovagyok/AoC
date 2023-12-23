#include <cstdint>

struct MyTreeEntry {
  uint64_t dest;
  uint64_t src;
  uint64_t len;
};

class MyTreeMap {
  MyTreeMap* left;
  MyTreeEntry entry;
  MyTreeMap* right;

 public:
  void insert(MyTreeEntry entry);
  uint64_t get(uint64_t num);
};
