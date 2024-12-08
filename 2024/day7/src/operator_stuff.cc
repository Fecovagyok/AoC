#include "operator_stuff.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <sstream>
#include <string>

#include "permutation.h"

static uint32_t max;

uint32_t get_max() { return max; }

uint64_t process_equation(const Equation& eq) {
  const opereands& ops = eq.ops;
  const uint32_t num_of_ops = ops.size() - 1;
  assert(num_of_ops < 12);
  max = std::max(max, num_of_ops);
  Permutation perm{num_of_ops};

  for (; true; perm.increase_whole()) {
    uint64_t sum = eq.ops[0];
    for (uint32_t idx = 0; idx < num_of_ops; idx++) {
      switch (perm.get_operation(idx)) {
        case OP_Addition:
          sum = sum + static_cast<uint64_t>(eq.ops[idx + 1]);
          break;
        case OP_Multiplication:
          sum *= static_cast<uint64_t>(eq.ops[idx + 1]);
          break;
        case OP_Whatever:
          sum = std::stoull(std::to_string(sum) +
                            std::to_string(eq.ops[idx + 1]));
          break;
      }
    }
    if (sum == eq.result) {
      return sum;
    }
    if (perm.is_end()) break;
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
