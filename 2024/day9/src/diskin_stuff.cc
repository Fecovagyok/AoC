#include "diskin_stuff.h"

#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

static char slurped[20000 + 1];
static uint64_t disk_map[sizeof(slurped) * 9];
static size_t disk_count = 0;

static const uint64_t FREE_SPACE_CHAR = UINT64_MAX;

static std::vector<size_t> free_space_index;

void slurp_it_whole(std::ifstream& input) {
  free_space_index.reserve(1000);
  input.getline(slurped, sizeof(slurped));
  for (size_t i = 0; slurped[i] != '\0'; i += 2) {
    for (char j = 0; j < slurped[i] - '0'; j++) {
      disk_map[disk_count] = i / 2;
      disk_count++;
    }
    if (slurped[i + 1] == '\0') break;
    for (char j = 0; j < slurped[i + 1] - '0'; j++) {
      disk_map[disk_count] = FREE_SPACE_CHAR;
      free_space_index.push_back(disk_count);
      disk_count++;
    }
  }
  disk_map[disk_count] = 0;
}

void compact_da_disk() {
  auto free_space_iter = free_space_index.begin();
  for (size_t i = 0; i < disk_count; i++) {
    size_t idx = disk_count - i - 1;
    if (disk_map[idx] == FREE_SPACE_CHAR) continue;
    if (free_space_iter == free_space_index.end() || *free_space_iter > idx)
      break;
    disk_map[*free_space_iter] = disk_map[idx];
    ++free_space_iter;
    disk_map[idx] = FREE_SPACE_CHAR;
  }
  uint64_t checksum = 0;
  for (size_t i = 0; i < disk_count; i++) {
    if (disk_map[i] == FREE_SPACE_CHAR) break;
    checksum += i * disk_map[i];
  }
  std::cout << checksum << std::endl;
}
