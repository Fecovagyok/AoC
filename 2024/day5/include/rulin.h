#pragma once

#include <cstdint>
#include <istream>
#include <string>
#include <unordered_map>
#include <vector>

using ruleset = std::vector<uint32_t>;

class Rules {
  std::unordered_map<uint32_t, ruleset> map;

 public:
  const ruleset& get_rule(uint32_t key) { return map[key]; }
  void read_rule(std::istream& input);
  static Rules& instance() {
    static Rules i;
    return i;
  }
};

void read_rules(std::string& rules);
