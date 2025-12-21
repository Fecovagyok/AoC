#include "machine_stuff.h"

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_set>
#include <utility>
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

class Variations {
  std::vector<uint32_t> vars;
  size_t num_of_buttons;
  size_t idx = 0;
  bool ended = false;

 public:
  Variations(uint32_t num_of_presses, size_t num_of_buttons)
      : vars(num_of_presses, 0), num_of_buttons(num_of_buttons) {}
  void next_variation() {
    bool reset = false;
    for (uint32_t i = 0; i < idx; i--) {
      uint32_t& position = vars.at(i);
      if (position + 1 >= num_of_buttons) {
        position = 0;
        reset = true;
      } else {
        position++;
        break;
      }
    }
    if (reset) {
      idx++;
      if (idx >= vars.size()) {
        ended = true;
      }
    }
  }

  void push_buttons(Machine& machine) {
    for (uint32_t i = 0; i < vars.size(); i++) {
      machine.press_button(vars[i]);
    }
  }

  bool has_next() const { return !ended; }
};

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

bool go_through_all_possibilites(uint32_t num, Machine& machine,
                                 Bulbs& excpected) {
  for (Variations variations{num, machine.buttons.size()};
       variations.has_next(); variations.next_variation()) {
    Machine copy = machine;
    variations.push_buttons(copy);
    if (copy.bulbs == excpected) {
      return true;
    }
  }
  return false;
}

uint64_t solve_machine(size_t idx) {
  Machine& machine = machine_at(idx);
  Bulbs expected = machine.bulbs;
  machine.startBulbs();
  auto max_iter = std::max_element(expected.cbegin(), expected.cend());
  uint32_t max = *max_iter * machine.buttons.size();

  for (uint32_t i = 1; i < max; i++) {
    if (go_through_all_possibilites(i, machine, expected)) {
      return i;
    }
  }
  throw std::runtime_error("sdalsdlaksd;askd");
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
