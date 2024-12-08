#include "operator_stuff.h"

#include <cassert>
#include <sstream>

uint64_t process_equation(const Equation& eq) {
  const opereands& ops = eq.ops;
  const uint32_t num_of_ops = ops.size() - 1;
  assert(num_of_ops < 32);

  for (uint32_t perm = 0; perm < (1 << num_of_ops); perm++) {
    uint64_t sum = eq.ops[0];
    for (uint32_t idx = 0; idx < num_of_ops; idx++) {
      if (perm & (1 << idx)) {
        sum = sum + static_cast<uint64_t>(eq.ops[idx + 1]);
      } else {
        sum *= static_cast<uint64_t>(eq.ops[idx + 1]);
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
