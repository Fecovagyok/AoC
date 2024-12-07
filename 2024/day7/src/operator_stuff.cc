#include "operator_stuff.h"

#include <cassert>
#include <cstdint>
#include <sstream>
#include <vector>

using opereands = std::vector<uint32_t>;

struct Equation {
  uint64_t result;
  opereands ops;
};

void process_equation(const Equation& eq) {
  const opereands& ops = eq.ops;
  for (size_t i = 1; i < ops.size(); i++) {
  }
}

void read_equation(std::string& buf) {
  std::istringstream input{buf};
  Equation eq;
  input >> eq.result;
  assert(!input.fail());
  {
    char xd = input.get();
    assert(xd == ':');
  }

  while (!input.eof()) {
    uint32_t num;
    input >> num;
    eq.ops.push_back(num);
  }
}
