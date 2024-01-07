#include "custom_tree.h"

void recur_get_intervals(MyTreeMap* root, std::vector<Interval>& intervals,
                         const Interval& seed) {
  if (root == nullptr) {
    intervals.push_back(seed);
    return;
  }

  const MyTreeEntry& entry = root->entry;
  const uint64_t end = seed.start + seed.len;
  const uint64_t entry_end = entry.src + entry.src;

  if (seed.start < entry.src) {
    if (end < entry.src) {
      recur_get_intervals(root->left, intervals, seed);
      return;
    }
    if (end <= entry_end) {
      recur_get_intervals(root->left, intervals,
                          {seed.start, entry.src - seed.start});
      // add seed entry.dest : entry.dest + seed_len
      intervals.push_back({entry.dest, end - entry.src});
      return;
    }
    // seed.start + seed.len >= entry.src + entry.len
    recur_get_intervals(root->left, intervals,
                        {seed.start, entry.src - seed.start});
    intervals.push_back({entry.dest, entry.len});
    recur_get_intervals(
        root->right, intervals,
        {entry_end, seed.len - (entry.src - seed.start) - entry.len});
    return;
  }
  if (seed.start <= entry_end) {
    const uint64_t start_offset = seed.start - entry.src;
    if (end <= entry_end) {
      intervals.push_back({entry.dest + start_offset, seed.len});
      return;
    }
    // end > entry_end
    intervals.push_back({entry.dest + start_offset, entry.len - start_offset});
    recur_get_intervals(root->right, intervals,
                        {entry_end, seed.len - (entry.len - start_offset)});
    return;
  }
  // seed_start > entry_end
  recur_get_intervals(root->right, intervals, seed);
}
