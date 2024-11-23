#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>

#include "aoc_reader.h"

#define INPUT_SIZE 215
#define WINNER_SIZE 10
#define MY_SIZE 25

uint16_t calcPoints(uint16_t count) {
  if (count == 0) return 0;

  uint16_t hatvany = 1;
  for (uint16_t i = 0; i < count - 1; i++) {
    hatvany = hatvany * 2;
  }
  return hatvany;
}

typedef std::vector<uint32_t> Card_t;

uint32_t winCards(Card_t& card, uint16_t count, uint16_t cardNum) {
  uint32_t cardQuota = card[cardNum - 1];
  uint32_t ret_count = 0;
  for (uint16_t i = cardNum; i < count + cardNum && i < card.size(); i++) {
    card[i] += cardQuota;
    ret_count += cardQuota;
  }
  return ret_count;
}

int main() {
  uint64_t points = 0;
  uint32_t cardNum = 1;
  Card_t cards(INPUT_SIZE, 1);
  auto process_line = [&](std::string& buf) {
    std::istringstream ss{buf};
    ss.ignore(buf.size(), ':');
    ss.ignore(buf.size(), ' ');
    std::unordered_set<uint16_t> winners(WINNER_SIZE);
    for (uint8_t i = 0; i < WINNER_SIZE; i++) {
      uint16_t in;
      ss >> in;
      winners.insert(in);
    }
    ss.ignore(3);
    uint16_t count = 0;
    for (uint16_t i = 0; i < MY_SIZE; i++) {
      uint16_t in;
      ss >> in;
      if (winners.find(in) != winners.cend()) {
        count++;
      }
    }
    points += winCards(cards, count, cardNum);
    cardNum++;
  };
  AoCReader reader{process_line, 270, "day4/input.txt"};
  reader.read();
  std::cout << points + INPUT_SIZE << std::endl;
}
