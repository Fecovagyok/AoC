#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

using BulbRef = size_t;

struct Button {
  std::vector<BulbRef> bulbs;
};

class Bulbs {
  std::vector<uint32_t> bulbs;

 public:
  // Bulbs() = default;
  // Bulbs(const Bulbs& other) = default;
  // Bulbs(Bulbs&& other) : bulbs(other.bulbs) {}
  // Bulbs& operator=(const Bulbs& other) = default;
  // Bulbs& operator=(Bulbs&& other) {
  //   bulbs = other.bulbs;
  //   return *this;
  // }

  size_t size() const { return bulbs.size(); }
  uint32_t& at(size_t idx) { return bulbs.at(idx); }
  uint32_t& operator[](size_t idx) { return this->at(idx); }
  uint32_t& emplace_back(uint32_t value) { return bulbs.emplace_back(value); }
  void reserve(size_t num) { bulbs.reserve(num); }

  uint32_t at_const(size_t idx) const { return bulbs.at(idx); }

  std::string bulbsToString() {
    std::string ret;
    ret.reserve(bulbs.size() * 3);
    for (size_t i = 0; i < bulbs.size() - 1; i++) {
      ret.append(std::to_string(bulbs[i]));
      ret.push_back(',');
    }
    ret.append(std::to_string(bulbs[bulbs.size() - 1]));
    return ret;
  }

  bool operator==(const Bulbs& other) const {
    if (&other == this) return true;
    if (other.bulbs.size() != bulbs.size()) return false;
    for (size_t i = 0; i < bulbs.size(); i++) {
      if (bulbs[i] != other.bulbs[i]) {
        return false;
      }
    }
    return true;
  }
};

struct Machine {
  Bulbs bulbs;
  std::vector<Button> buttons;

  void startBulbs() {
    for (size_t i = 0; i < bulbs.size(); i++) {
      bulbs[i] = 0;
    }
  }

  std::string bulbsToString() {
    std::string ret;
    ret.reserve(bulbs.size() * 3);
    for (size_t i = 0; i < bulbs.size() - 1; i++) {
      ret.append(std::to_string(bulbs[i]));
      ret.push_back(',');
    }
    ret.append(std::to_string(bulbs[bulbs.size() - 1]));
    return ret;
  }

  void press_button(size_t idx) {
    Button& button = buttons[idx];
    for (size_t i = 0; i < button.bulbs.size(); i++) {
      bulbs.at(button.bulbs[i])++;
    }
  }

  template <typename... Indicies>
  void press_multiple_buttons(Indicies... args) {
    (this->press_button(args), ...);
  }

  bool test_machine();
};

void solve_all_machines();
bool test_all_machines();
void parse_that(std::string& line);
Machine& machine_at(size_t idx);
