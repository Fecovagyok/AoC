#include "diskin_stuff.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <list>
#include <vector>

static const uint64_t FREE_SPACE_CHAR = UINT64_MAX;

struct MyFile {
  uint64_t id;
  uint16_t size;
  uint64_t start_idx;
  bool is_free_space() const { return id == FREE_SPACE_CHAR; }
};

static char slurped[20000 + 1];
std::list<MyFile> final_map;

using MyIndex = std::list<MyFile>::iterator;
static MyIndex disk_map[sizeof(slurped)];
static size_t disk_count = 0;
static std::vector<MyIndex> free_space_index;

void slurp_it_whole(std::ifstream& input) {
  free_space_index.reserve(5000);
  input.getline(slurped, sizeof(slurped));
  uint64_t curr_idx = 0;
  for (size_t i = 0; slurped[i] != '\0'; i += 2) {
    MyIndex file = final_map.insert(
        final_map.end(),
        MyFile{i / 2, static_cast<uint16_t>(slurped[i] - '0'), curr_idx});
    disk_map[disk_count] = file;
    curr_idx += file->size;
    disk_count++;
    if (slurped[i + 1] == '\0') break;
    file = final_map.insert(
        final_map.end(),
        MyFile{FREE_SPACE_CHAR, static_cast<uint16_t>(slurped[i + 1] - '0'),
               curr_idx});
    disk_map[disk_count] = file;
    free_space_index.push_back(file);
    curr_idx += file->size;
    disk_count++;
  }
}

void compact_da_disk() {
  for (size_t i = 0; i < disk_count; i++) {
    size_t idx = disk_count - i - 1;
    MyIndex file = disk_map[idx];
    if (file->is_free_space()) continue;
    uint16_t size = file->size;
    auto found_space = std::find_if(
        free_space_index.begin(), free_space_index.end(),
        [size](MyIndex free_size) { return free_size->size >= size; });
    if (found_space == free_space_index.end()) continue;
    MyIndex space_pos = *found_space;
    if (space_pos->start_idx > file->start_idx) continue;
    MyIndex inserted = final_map.insert(space_pos, *file);
    file->id = FREE_SPACE_CHAR;
    inserted->start_idx = space_pos->start_idx;
    space_pos->size -= size;
    space_pos->start_idx += size;
  }
  uint64_t checksum = 0;
  uint64_t position = 0;
  for (const MyFile& file : final_map) {
    if (file.is_free_space()) {
      position += file.size;
      continue;
    }
    assert(file.start_idx == position);
    for (uint16_t i = 0; i < file.size; i++) {
      checksum += (position + i) * file.id;
    }
    position += file.size;
  }
  std::cout << checksum << std::endl;
}
