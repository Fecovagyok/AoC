#pragma once

#include <string>
#include <vector>

struct Bulb {
  const char wanted_state;
  char current_state;

  void flip() {
    if (current_state == '.') {
      current_state = '#';
    } else {
      current_state = '.';
    }
  }
};

using BulbRef = size_t;

struct Button {
  std::vector<BulbRef> bulbs;
};

struct Machine {
  std::vector<Bulb> bulbs;
  std::vector<Button> buttons;

  void press_button(size_t idx) {
    Button& button = buttons[idx];
    for (size_t i = 0; i < button.bulbs.size(); i++) {
      bulbs[button.bulbs[i]].flip();
    }
  }

  bool test_machine();
};

bool test_all_machines();
void parse_that(std::string& line);
Machine& machine_at(size_t idx);
