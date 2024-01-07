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

  if (seed.seed_len == 0) return;

  MyTreeEntry& entry = root->entry;
  int64_t low_len = std::min(entry.src - seed.seed_start, seed.seed_len);
  if (low_len > 0) {
    recur_get_intervals(root->left, intervals,
                        {seed.seed_start, (uint64_t)low_len});
  }
  uint64_t middle_start = low_len > 0 ? entry.src : entry.src - low_len;
  int64_t middle_len =
      seed.seed_start + seed.seed_len - (entry.src + entry.len);

  if (middle_len > 0) {
    intervals.push_back({middle_start, static_cast<uint64_t>(middle_len)});
  }

  if (seed.seed_start < entry.src) {
    if (seed.seed_start + seed.seed_len < entry.src) {
      recur_get_intervals(root->left, intervals, seed);
      return;
    }
    if (seed.seed_start + seed.seed_len < entry.src + entry.len) {
      recur_get_intervals(root->left, intervals,
                          {seed.seed_start, entry.src - seed.seed_start});
      // add seed entry.dest : entry.dest + seed_len
      intervals.push_back(
          {entry.dest, seed.seed_len - (entry.src - seed.seed_start)});
      return;
    }
    // seed.start + seed.len >= entry.src + entry.len
    recur_get_intervals(root->left, intervals,
                        {seed.seed_start, entry.src - seed.seed_start});
    intervals.push_back({entry.dest, entry.len});
    recur_get_intervals(
        root->right, intervals,
        {entry.src + entry.len,
         seed.seed_len - (entry.src - seed.seed_start) - entry.len});
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
