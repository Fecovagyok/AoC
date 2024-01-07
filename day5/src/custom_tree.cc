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
                         const Seed& seed) {
  if (root == nullptr) {
    intervals.push_back(seed);
    return;
  }

  const MyTreeEntry& entry = root->entry;
  const uint64_t end = seed.seed_start + seed.seed_len;
  const uint64_t entry_end = entry.src + entry.src;

  if (seed.seed_start < entry.src) {
    if (end < entry.src) {
      recur_get_intervals(root->left, intervals, seed);
      return;
    }
    if (end <= entry_end) {
      recur_get_intervals(root->left, intervals,
                          {seed.seed_start, entry.src - seed.seed_start});
      // add seed entry.dest : entry.dest + seed_len
      intervals.push_back({entry.dest, end - entry.src});
      return;
    }
    // seed.start + seed.len >= entry.src + entry.len
    recur_get_intervals(root->left, intervals,
                        {seed.seed_start, entry.src - seed.seed_start});
    intervals.push_back({entry.dest, entry.len});
    recur_get_intervals(
        root->right, intervals,
        {entry_end, seed.seed_len - (entry.src - seed.seed_start) - entry.len});
    return;
  }
  if (seed.seed_start <= entry_end) {
    const uint64_t start_offset = seed.seed_start - entry.src;
    if (end <= entry_end) {
      intervals.push_back({entry.dest + start_offset, seed.seed_len});
      return;
    }
    // end > entry_end
    intervals.push_back({entry.dest + start_offset, entry.len - start_offset});
    recur_get_intervals(
        root->right, intervals,
        {entry_end, seed.seed_len - (entry.len - start_offset)});
    return;
  }
  // seed_start > entry_end
  recur_get_intervals(root->right, intervals, seed);
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

uint64_t MyTreeMap::get_min(const Seed& seed) {}

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
