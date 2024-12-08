#pragma once

#include <cstdint>
#include <string>
#include <vector>

using opereands = std::vector<uint32_t>;

struct Equation {
  uint64_t result;
  opereands ops;
};

Equation read_equation(std::string& buf);
uint64_t process_equation(const Equation& eq);
uint32_t get_max();
