#pragma once

#include <cstdint>

enum F_Operator { OP_Addition = 0, OP_Multiplication = 1, OP_Whatever = 2 };

class Permutation {
  /* 3*4 = 12 => 11 max perms */
  uint8_t perms[3] = {0, 0, 0};
  uint32_t quantity;

  uint8_t increase_half(uint8_t half) {
    uint8_t A = half & 1;
    uint8_t B = (half >> 1) & 1;
    uint8_t C = (half >> 2) & 1;
    uint8_t D = (half >> 3) & 1;

    return (((D && !B) || (C && B)) << 3) |
           (((B && !C && !D) || (!B && C)) << 2) | (A << 1) | (!A && !B);
  }

  uint8_t increase_one(uint8_t one) {
    uint8_t first_half = one & 0x0f;
    uint8_t second_half = one >> 4;

    first_half = increase_half(first_half);
    if (first_half == 0) {
      second_half = increase_half(second_half);
    }
    return (second_half << 4) | first_half;
  }

  void increase_recurse(uint8_t idx) {
    if (idx == sizeof(perms)) {
      return;
    }
    uint8_t val = increase_one(perms[idx]);
    perms[idx] = val;
    if (val == 0) {
      increase_recurse(idx + 1);
    }
  }

 public:
  Permutation(uint32_t q);
  bool is_end() {
    uint32_t big_idx = quantity / 4;
    for (size_t i = 0; i < big_idx; i++) {
      if (perms[i] != 0xAA) {
        return false;
      }
    }
    /* Quantity is sanitized */
    uint8_t small_idx = static_cast<uint8_t>(quantity) % 4;
    uint8_t test = 0;
    for (uint8_t i = 0; i < small_idx; i++) {
      test = (test << (2 * i)) | 2;
    }

    if (test != perms[big_idx]) {
      return false;
    }
    return true;
  }

  F_Operator get_operation(uint8_t idx) {
    uint8_t big_idx = idx / 4;
    uint8_t small_idx = idx % 4;

    uint8_t perm = perms[big_idx];
    return static_cast<F_Operator>((perm >> (small_idx * 2)) & 3);
  }
  void increase_whole() { increase_recurse(0); }
};
