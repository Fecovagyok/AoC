#pragma once

#include <cstdint>
#include <fstream>
#include <vector>

using Stones = std::vector<uint64_t>;

void read_stones(std::ifstream& input);
