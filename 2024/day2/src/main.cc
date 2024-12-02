#include <aoc_reader.h>

#include <cstdint>
#include <cstdlib>
#include <ostream>
#include <sstream>
#include <vector>

using Matrix = std::vector<std::vector<uint32_t>>;

enum class DescendType { Descending, Ascending, Either };

#define PROBLEMATIC(ascend) \
  do {                      \
    problematic++;          \
    break;                  \
  } while (0)

#define VERY_PROBLEMATIC()              \
  do {                                  \
    if (very_problematic) return false; \
    very_problematic = true;            \
    break;                              \
  } while (0)

bool process_row(std::vector<uint32_t>& row, std::istream& input) {
  uint32_t in_prev;
  DescendType type = DescendType::Either;
  input >> in_prev;
  if (input.eof() || input.fail()) {
    std::cerr << "Baj2" << std::endl;
    std::exit(1);
  }
  uint32_t count = 0;
  uint32_t problematic = 0;
  bool very_problematic = true;
  while (true) {
    uint32_t in;
    input >> in;
    if (input.fail()) {
      std::cerr << "Baj" << std::endl;
      std::exit(1);
    }
    row.push_back(in);
    if (in_prev == in) {
      /* Unsafe */
      VERY_PROBLEMATIC();
    }
    switch (type) {
      case DescendType::Either:
        type = in_prev > in ? DescendType::Descending : DescendType::Ascending;
        break;
      case DescendType::Descending:
        if (in_prev < in) {
          /* Unsafe */
          PROBLEMATIC();
        }
        break;
      case DescendType::Ascending:
        if (in_prev > in) {
          PROBLEMATIC();
        }
    }
    uint32_t bigger = in_prev > in ? in_prev : in;
    uint32_t smaller = in_prev > in ? in : in_prev;
    if (bigger - smaller > 3) {
      /*Unsafe*/
      return false;
    }
    if (input.eof()) break;
    in_prev = in;
    count++;
  }
  return true;
}

int main() {
  Matrix matrix;
  matrix.reserve(1000);
  uint32_t count = 0;
  auto cb = [&matrix, &count](std::string& buf) {
    if (buf.empty()) return;
    std::istringstream input{buf};
    std::vector<uint32_t> row;
    if (process_row(row, input)) {
      std::cout << buf << " -- Safe\n";
      count++;
    }
    if (row.size() != 0) matrix.push_back(std::move(row));
  };
  AoCReader reader{cb, 260, "2024/day2/input.txt"};
  reader.read();

  std::cout << count << std::endl;
  return 0;
}
