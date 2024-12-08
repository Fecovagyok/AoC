#include "operator_stuff.h"

#include <cassert>
#include <sstream>

uint64_t process_equation(const Equation& eq) {
  const opereands& ops = eq.ops;
  const uint32_t num_of_ops = ops.size() - 1;
  assert(num_of_ops < 32);

  for (uint32_t i = 0; i < (1 << num_of_ops); i++) {
    uint64_t sum = eq.ops[0];
    for (uint32_t j = 0; j < num_of_ops; j++) {
      if (i & (1 << j)) {
        sum = sum + static_cast<uint64_t>(eq.ops[j + 1]);
      } else {
        sum *= static_cast<uint64_t>(eq.ops[j + 1]);
      }
    }
    if (sum == eq.result) {
      return sum;
    }
  }
  return 0;
}

Equation read_equation(std::string& buf) {
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
  return eq;
}
