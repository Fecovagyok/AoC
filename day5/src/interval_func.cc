#include "custom_tree.h"

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
