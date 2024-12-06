#include "rulin.h"

#include <algorithm>
#include <sstream>

void Rules::read_rule(std::istream& input) {
  uint32_t depend, page;
  input >> depend;
  input.ignore(1);
  input >> page;
  map[page].push_back(depend);
  inverse_map[depend].push_back(page);
}
void read_rules(std::string& rules) {
  std::istringstream input{rules};
  Rules& rule_storage = Rules::instance();
  rule_storage.read_rule(input);
}
