#include "machine_stuff.h"

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

bool Machine::test_machine() {
  for (size_t i = 0; i < bulbs.size(); i++) {
    if (bulbs[i].current_state != bulbs[i].wanted_state) {
      // std::cout << "Fail\n";
      return false;
    }
  }
  std::cout << "Pass\n";
  return true;
}

std::vector<Machine> tasks;

Machine& machine_at(size_t idx) { return tasks.at(idx); }

void parse_that(std::string& line) {
  // Missing split functionality, lol
  std::vector<std::string_view> pieces = split(line);
  // Last piece missing, but currently I dont care
  std::string_view bulb_view = pieces.at(0);
  Machine& machine = tasks.emplace_back();
  machine.bulbs.reserve(bulb_view.size() - 2);
  for (size_t i = 1; i < bulb_view.size() - 1; i++) {
    machine.bulbs.emplace_back(bulb_view.at(i), '.');
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
      button.bulbs.emplace_back(str_to_int(bulb_refs[i]));
    }
  }
}

uint64_t solve_machine(size_t idx) {
  Machine& machine = machine_at(idx);
  std::queue<std::pair<std::string, uint32_t>> meglatogantando_cucsok;
  meglatogantando_cucsok.emplace(std::make_pair(machine.bulbToString(), 0));
  std::unordered_set<std::string> latogatott_csucsok;
  while (meglatogantando_cucsok.size() > 0) {
    auto current = meglatogantando_cucsok.front();
    std::string current_string = current.first;
    if (current_string == machine.bulbToExpectedString()) {
      return current.second;
    }
    meglatogantando_cucsok.pop();
    if (latogatott_csucsok.contains(current_string)) {
      continue;
    }
    latogatott_csucsok.insert(current_string);
    for (uint64_t i = 0; i < machine.buttons.size(); i++) {
      std::vector<BulbRef>& bulbs = machine.buttons[i].bulbs;
      auto copy = current;
      for (size_t i = 0; i < bulbs.size(); i++) {
        size_t idx = bulbs[i];
        flip(copy.first, idx);
      }
      if (!latogatott_csucsok.contains(copy.first)) {
        copy.second++;
        meglatogantando_cucsok.emplace(std::move(copy));
      }
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
