#include "custom_tree.h"

#include <cstdint>

namespace {}

// Suppose non-overlapping entries
void MyTreeMap::insert(MyTreeEntry in_entry) {}

uint64_t MyTreeMap::get(uint64_t num) {
  if (num < entry.src) {
    if (left == nullptr) return num;
    return left->get(num);
  }
  if (num >= entry.src + entry.len) {
    if (right == nullptr) return num;
    return right->get(num);
  }
  return (num - entry.src) + entry.dest;
}
