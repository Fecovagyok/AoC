#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

using Dataset = std::vector<int32_t>;

void part_one(std::ifstream& input) {
  Dataset left, right;
  while (true) {
    int32_t tmp_left, tmp_right;
    input >> tmp_left >> tmp_right;
    if (input.eof() || input.fail()) break;
    left.push_back(tmp_left);
    right.push_back(tmp_right);
  }

  if (left.size() != right.size()) {
    std::cerr << "Baj" << std::endl;
    std::exit(1);
  }
  std::sort(left.begin(), left.end());
  std::sort(right.begin(), right.end());

  uint32_t sum = 0;
  for (size_t i = 0; i < left.size(); i++) {
    sum += std::abs(left[i] - right[i]);
  }
  std::cout << sum << std::endl;
}

void part_two(std::ifstream& input) {
  std::unordered_map<uint32_t, uint32_t> right;
  std::vector<uint32_t> left;
  left.reserve(1000);
  right.reserve(1000);

  while (true) {
    uint32_t tmp_left, right_key;
    input >> tmp_left >> right_key;

    if (input.eof()) break;

    left.push_back(tmp_left);
    if (right.find(right_key) == right.end()) {
      right[right_key] = 1;
    } else {
      right[right_key]++;
    }
  }
  uint32_t sum = 0;
  for (size_t i = 0; i < left.size(); i++) {
    if (right.find(left[i]) != right.end()) {
      sum += left[i] * right[left[i]];
    }
  }
  std::cout << sum << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::ifstream input{"./2024/day1/input.txt"};
  if (input.fail()) {
    std::cerr << "F" << std::endl;
    return 1;
  }
  part_two(input);
  return 0;
}
