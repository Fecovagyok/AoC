#include <diskin_stuff.h>

int main() {
  std::ifstream input{"./2024/day9/input.txt"};
  slurp_it_whole(input);
  compact_da_disk();
  return 0;
}
