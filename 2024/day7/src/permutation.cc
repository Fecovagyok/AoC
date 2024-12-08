#include "permutation.h"

#include <cassert>

Permutation::Permutation(uint32_t q) : quantity(q) { assert(q < 12); }
