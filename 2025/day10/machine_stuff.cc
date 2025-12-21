#include "machine_stuff.h"

#include <cctype>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include "me_conversion.h"
#include "me_split.h"

void flip(std::string& kalap, size_t i) {
  char& current_state = kalap.at(i);
  if (current_state == '.') {
    current_state = '#';
  } else {
    current_state = '.';
  }
}

namespace std {
template <>
struct hash<Bulbs> {
  std::size_t operator()(const Bulbs& bulbs) const noexcept {
    std::size_t hash = 0;
    for (size_t i = 0; i < bulbs.size(); i++) {
      hash ^= (static_cast<size_t>(bulbs.at_const(i)) << i * 7);
    }
    return hash;
  }
};
}  // namespace std

bool Machine::test_machine() { return true; }

std::vector<Machine> tasks;

Machine& machine_at(size_t idx) { return tasks.at(idx); }

void parse_that(std::string& line) {
  // Missing split functionality, lol
  std::vector<std::string_view> pieces = split(line);
  // Last piece missing, but currently I dont care
  std::string_view bulb_view_with_brackets = pieces.at(pieces.size() - 1);
  std::string_view bulb_view =
      bulb_view_with_brackets.substr(1, bulb_view_with_brackets.size() - 2);
  std::vector<std::string_view> bulb_pieces = split(bulb_view, ',');
  Machine& machine = tasks.emplace_back();
  machine.bulbs.reserve(bulb_pieces.size());
  for (size_t i = 0; i < bulb_pieces.size(); i++) {
    machine.bulbs.emplace_back(str_to_int32(bulb_pieces[i]));
  }

  machine.buttons.reserve(pieces.size() - 1);
  // Negative one, so {} is ignored
  for (size_t i = 1; i < pieces.size() - 1; i++) {
    std::string_view noob_view = pieces.at(i);
    std::string_view wire_view = noob_view.substr(1, noob_view.size() - 2);
    auto bulb_refs = split(wire_view, ',');
    static_assert(sizeof(uint64_t) == sizeof(size_t));
    Button& button = machine.buttons.emplace_back();
    button.bulbs.reserve(bulb_refs.size());
    for (size_t i = 0; i < bulb_refs.size(); i++) {
      button.bulbs.emplace_back(str_to_int64(bulb_refs[i]));
    }
  }
}

uint64_t solve_machine(size_t idx) {
  Machine& machine = machine_at(idx);
  Bulbs expected = machine.bulbs;
  machine.startBulbs();
  return 0;
}

void solve_all_machines() {
  uint64_t sum = 0;
  for (size_t i = 0; i < tasks.size(); i++) {
    sum += solve_machine(i);
  }
  std::cout << sum << std::endl;
}

bool test_all_machines() {
  for (auto& machine : tasks) {
    if (!machine.test_machine()) {
      return false;
    }
  }
  return true;
}
