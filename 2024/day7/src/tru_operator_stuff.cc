#include "tru_operator_stuff.h"

#include <cstdint>
#include <vector>

struct Operator {
  virtual uint64_t operate(uint32_t left, uint32_t right) const = 0;
};

struct Addition : public Operator {
  static Addition* instance() {
    static Addition i;
    return &i;
  }
  uint64_t operate(uint32_t left, uint32_t right) const override {
    return static_cast<uint64_t>(left) + static_cast<uint64_t>(right);
  }
};

struct Multiplication : public Operator {
  static Multiplication* instance() {
    static Multiplication i;
    return &i;
  }
  uint64_t operate(uint32_t left, uint32_t right) const override {
    return static_cast<uint64_t>(left) * static_cast<uint64_t>(right);
  }
};

using one_perm = std::vector<Operator>;
using all_perms = std::vector<one_perm>;

void create_perm(uint32_t how_many) {
  const Operator* ops[] = {Addition{}, Multiplication{}};
  all_perms all;
  all.reserve(1 << how_many);
}
