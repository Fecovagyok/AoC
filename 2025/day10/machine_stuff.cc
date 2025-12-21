#include "machine_stuff.h"

#include <ortools/linear_solver/linear_solver.h>

#include <cassert>
#include <cctype>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include "me_conversion.h"
#include "me_split.h"

using namespace operations_research;

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
  Bulbs& bulbs = machine.bulbs;
  auto& buttons = machine.buttons;
  std::unique_ptr<MPSolver> solver(MPSolver::CreateSolver("CBC"));
  if (!solver) {
    std::cerr << "Noobs" << std::endl;
    return 0;
  }

  std::vector<MPVariable*> variables;
  variables.reserve(buttons.size());

  MPObjective* const objective = solver->MutableObjective();

  for (size_t i = 0; i < buttons.size(); i++) {
    std::string name = "x";
    name.append(std::to_string(i));
    MPVariable* var = solver->MakeIntVar(0.0, 1000.0, name);
    objective->SetCoefficient(var, 1);
    variables.push_back(var);
  }

  for (size_t i = 0; i < bulbs.size(); i++) {
    // Constraints
    std::string name2 = "eq";
    name2.append(std::to_string(i));
    MPConstraint* const eq =
        solver->MakeRowConstraint(bulbs[i], bulbs[i], name2);

    std::vector<size_t> button_dependencies;

    for (size_t j = 0; j < buttons.size(); j++) {
      Button& button = buttons[j];
      for (size_t& wire : button.bulbs) {
        if (wire == i) {
          eq->SetCoefficient(variables[j], 1.0);
          button_dependencies.push_back(j);
        }
      }
    }
    assert(button_dependencies.size() > 0);
  }

  const MPSolver::ResultStatus result_status = solver->Solve();
  if (result_status != MPSolver::OPTIMAL) {
    std::cerr << "Not optimal " << result_status << std::endl;
    return 0;
  }

  return objective->Value();
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
