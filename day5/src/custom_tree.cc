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

std::vector<Seed> MyTreeMap::get_min(const Seed& seed) {
  std::vector<Seed> intervals;
  recur_get_intervals(this, intervals, seed);
  return intervals;
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
