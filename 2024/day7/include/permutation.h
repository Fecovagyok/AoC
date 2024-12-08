#pragma once

#include <cstdint>

class Permutation {
  /* 3*4 = 12 => 11 max perms */
  uint8_t perms[3];

  bool increase_one(uint8_t& one) {
    switch (one) {
      case 0x0:
        one = 0x1;
        return false;
      case 0x1:
        one = 0x2;
        return false;
      case 0x2:
        one = 0x4;
        return false;
      case 0x4:
        one = 0x5;
        return false;
      case 0x5:
        one = 0x6;
        return false;
      case 0x6:
        one = 0x8;
        return false;
    }
  }
};
