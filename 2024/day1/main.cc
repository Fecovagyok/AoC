#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::ifstream input{"./2024/day1/input.txt"};
  if (input.fail()) {
    std::cerr << "F" << std::endl;
    return 1;
  }

  std::vector<int32_t> left, right;
  left.reserve(5000);
  right.reserve(5000);

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
  return 0;
}
