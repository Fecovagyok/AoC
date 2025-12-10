#include <aoc_reader.h>

#include <regex>

struct Bulb {
  char initial_state;
  char cuurent_state;
};

using BulbRef = int;

struct Button {
  std::vector<BulbRef> bulbs;
};

struct Machine {
  std::vector<Bulb> bulbs;
  std::vector<Button> buttons;
};

int main() {
  // std::regex pattern{"\\[*[(.#]+)\\]\\s+ (\\(\\d)(?:,(\\d))+\\)"};
  std::regex pattern_first{"\\[([.#]+)\\]\\s+ (\\(\\d(?:,\\d)+)+"};
  std::smatch match;
  auto cb = [&pattern_first, &match](std::string& line) {
    bool matched = std::regex_search(line, match, pattern_first);
    if (!matched) {
      std::cerr << "Wtf?" << std::endl;
      return;
    }
    std::cout << match[0];

    std::cout << line << std::endl;
  };
  AoCReader reader{cb, 1024, "2025/day10/input1.txt"};
  reader.read();
  return 0;
}
