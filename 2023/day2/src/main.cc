#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define BUFF_SIZE 250

#define COLOURS \
  X(red)        \
  X(green)      \
  X(blue)

#define F_COMPARE(arg)                         \
  else if (std::strcmp(stat_buf, #arg) == 0) { \
    arg = current;                             \
  }

struct Round {
#define X(colour) int64_t colour = -1;
  COLOURS
#undef X

  uint16_t read_round(const std::string_view buf,
                      std::string_view::const_iterator& it) {
    char stat_buf[6];
    while (it < buf.cend()) {
      if (*it == ';') return 0;
      if (*it == ',') {
        it += 2;
        continue;
      }
      uint64_t current;
      if (sscanf(it, "%lld %5[rbgendul]", &current, stat_buf) != 2) {
        std::cerr << "Rossz input: " << buf << std::endl;
        exit(EXIT_FAILURE);
      }
#define X F_COMPARE
      COLOURS
#undef X
      else {
        std::cerr << "Rossz input: " << buf << std::endl;
        exit(EXIT_FAILURE);
      }
      size_t to_skip = std::to_string(current).size() + strlen(stat_buf) + 1;
      it += to_skip;
    }
    return 0;
  }

  int64_t cube() { return red * blue * green; }
};

struct Game {
  uint64_t id;
  std::vector<Round> rounds;
  Round max = {0, 0, 0};

#define F_STUFF(arg)                        \
  for (Round round : rounds) {              \
    max.arg = std::max(max.arg, round.arg); \
  }

  void process_rounds() {
    F_STUFF(blue);
    F_STUFF(red);
    F_STUFF(green);
  }

  Game() { rounds.reserve(10); }
  size_t read_game(const std::string_view buf,
                   std::string_view::const_iterator& it) {
    while (true) {
      Round round;
      round.read_round(buf, it);
      rounds.push_back(round);
      if (it >= buf.cend()) break;
      if (*it != ';') {
        std::printf("Rossz beolvasas: %s:%d\n", __func__, __LINE__);
        exit(EXIT_FAILURE);
      }
      it += 2;
    }
    return 0;
  }
};

uint64_t mr_logic(const std::string_view buf) {
  Game game;
  std::sscanf(buf.data(), "Game %lld: ", &(game.id));
  auto id = std::to_string(game.id);
  size_t to_skip = sizeof("Game : ") - 1 + id.size();
  auto it = buf.cbegin() + to_skip;
  game.read_game(buf, it);
  game.process_rounds();
  std::printf("Valid game: %s,%lld\n", buf.data(), game.max.red);
  return game.max.cube();
}

int main() {
  std::ifstream input{"input.txt"};
  if (input.fail()) {
    std::cout << "Balfasz" << std::endl;
    return 1;
  }

  std::string buf;
  buf.reserve(BUFF_SIZE);
  uint64_t osszeg = 0;
  while (true) {
    std::getline(input, buf);
    if (input.eof()) {
      break;
    }
    if (input.fail()) {
      std::cout << "Balfasz" << std::endl;
      return 1;
    }
    osszeg += mr_logic(buf);
    // std::cout << buf << "\n";
  }
  std::cout << osszeg << std::endl;

  return 0;
}
