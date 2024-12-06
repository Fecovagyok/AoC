#pragma once

#include <cstdint>
#include <istream>
#include <string>
#include <unordered_map>
#include <vector>

using ruleset = std::vector<uint32_t>;
using RuleMap = std::unordered_map<uint32_t, ruleset>;

class Rules {
  RuleMap map;
  RuleMap inverse_map;

 public:
  const ruleset& get_rule(uint32_t key) { return map[key]; }
  void sort_all();
  void read_rule(std::istream& input);
  static Rules& instance() {
    static Rules i;
    return i;
  }
};

void read_rules(std::string& rules);
