#include "tru_operator_stuff.h"

#include <cstdint>
#include <functional>
#include <vector>

using operator_ptr = std::function<uint64_t>;

using one_perm = std::vector<Operator>;
using all_perms = std::vector<one_perm>;

void create_perm(uint32_t how_many) {
  const Operator* ops[] = {Addition{}, Multiplication{}};
  all_perms all;
  all.reserve(1 << how_many);
}
