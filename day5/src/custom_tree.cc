#include "custom_tree.h"

#include <cstdint>
#include <vector>

// Suppose non-overlapping entries
MyTreeMap* recur_insert(MyTreeMap* root, const MyTreeEntry& entry) {
  if (root == nullptr) {
    MyTreeMap* new_entry = new MyTreeMap{};
    new_entry->entry = entry;
    new_entry->elements++;
    return new_entry;
  }
  if (entry.src < root->getSrc())
    root->left = recur_insert(root->left, entry);
  else if (entry.src > root->getSrc())
    root->right = recur_insert(root->right, entry);
  else
    throw "Baj";

  return root;
}

void recur_get_intervals(MyTreeMap* root, std::vector<Seed>& intervals,
                         const Seed& interval) {
  if (root == nullptr) {
    intervals.push_back(interval);
    return;
  }
}

void MyTreeMap::insert(const MyTreeEntry& in_entry) {
  if (elements == 0)
    entry = in_entry;
  else
    recur_insert(this, in_entry);
  elements++;
}

uint64_t MyTreeMap::get(uint64_t num) const {
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

uint64_t MyTreeMap::get_min(const Seed& seed) {
  if (seed.seed_start < entry.src) {
    if (seed.seed_start + seed.seed_len < entry.src) {
      if (left == nullptr) return seed;
      return left->get_min(seed);
    }
    if (seed.seed_start + seed.seed_len <= entry.src + entry.len) {
      if (left == nullptr) {
        return 0;  // add seed [seed_start:entry.src]
      }
      // add seed entry.dest : entry.dest + seed_len
      return left->get_min(seed);
    }
  }
  return 0;
}

MyTreeMap::~MyTreeMap() {
  if (left != nullptr) {
    delete left;
  }
  if (left != nullptr) {
    delete right;
  }
}

void MyTreeMap::read(std::istream& file) {
  MyTreeEntry local_entry;
  file >> local_entry.dest;
  file >> local_entry.src;
  file >> local_entry.len;
  insert(local_entry);
}
