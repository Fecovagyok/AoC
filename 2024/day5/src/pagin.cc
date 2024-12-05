#include "pagin.h"

#include <stddef.h>

#include <cstdint>
#include <istream>
#include <sstream>

#include "rulin.h"

// class Pages {};

using Pages = std::vector<uint32_t>;

bool is_pagin_valid(const Pages& pages) {
  for (size_t i = 0; i < pages.size(); i++) {
    const ruleset& rules = Rules::instance().get_rule(pages[i]);
    for (size_t j = i; j < pages.size(); j++) {
      for (size_t k = 0; k < rules.size(); k++) {
        if (rules[k] == pages[j]) {
          return false;
        }
      }
    }
  }
  return true;
}

uint32_t read_pages(std::string& pages) {
  std::istringstream input{pages};
  uint32_t page;
  Pages page_storage;
  while (!input.fail()) {
    char kalap;
    input >> page;
    page_storage.push_back(page);
    input >> kalap;
  }
  if (is_pagin_valid(page_storage)) {
    return page_storage[page_storage.size() / 2];
  }
  return 0;
}
