#include "machine_stuff.h"

#include <cctype>
#include <cstddef>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include "me_conversion.h"
#include "me_split.h"

bool Machine::test_machine() {
  for (size_t i = 0; i < bulbs.size(); i++) {
    if (bulbs[i].current_state != bulbs[i].wanted_state) {
      std::cout << "Fail\n";
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
  for (size_t i = 1; i < pieces.size(); i++) {
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

bool test_all_machines() {
  for (auto& machine : tasks) {
    if (!machine.test_machine()) {
      return false;
    }
  }
  return true;
}
