#include "pagin.h"

#include <stddef.h>

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <istream>
#include <sstream>

#include "rulin.h"

// class Pages {};

using Pages = std::vector<uint32_t>;

bool is_loner_node(const ruleset& rules, const Pages& pages) {
  for (size_t i = 0; i < rules.size(); i++) {
    for (size_t j = 0; j < pages.size(); j++) {
      if (rules[i] == pages[i]) return false;
    }
  }
  return true;
}

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

struct Dependent_node {
  uint32_t page;
  Pages remaining_dependencies;
  Dependent_node(uint32_t page, const ruleset& rules)
      : page(page), remaining_dependencies(rules) {}
};

using DepPages = std::vector<Dependent_node>;

void my_inner_sort_cycle(Pages& independent, DepPages& dependent) {
  for (size_t i = 0; i < independent.size(); i++) {
    uint32_t page = independent[i];
    auto found = std::find_if(
        dependent.begin(), dependent.end(),
        [page](Dependent_node& item) { return item.page == page; });
    if (found == dependent.end()) continue;

    Pages& node_deps = found->remaining_dependencies;
    auto found2 = std::find(node_deps.begin(), node_deps.end(), independent[i]);
    assert(found2 != node_deps.end());
    node_deps.erase(found2);
  }

  independent.clear();

  for (size_t i = 0; i < dependent.size(); i++) {
    if (dependent[i].remaining_dependencies.size() == 0) {
      independent.push_back(dependent[i].page);
    }
  }
  auto new_begin = std::remove_if(
      dependent.begin(), dependent.end(), [](Dependent_node& item) {
        return item.remaining_dependencies.size() == 0;
      });

  dependent.erase(new_begin, dependent.end());
}

void do_my_sort(Pages& pages) {
  Pages independent;
  DepPages dependent;
  Pages output;
  // Go through pages check if they're independent
  for (size_t i = 0; i < pages.size(); i++) {
    const ruleset& rules = Rules::instance().get_rule(pages[i]);
    if (is_loner_node(rules, pages)) {
      independent.push_back(pages[i]);
    } else {
      dependent.emplace_back(pages[i], rules);
    }
  }
  while (true) {
    output.insert(output.end(), independent.begin(), independent.end());
    if (output.size() == pages.size()) break;
    my_inner_sort_cycle(independent, dependent);
  }
  pages = output;
}

uint32_t read_pages(std::string& pages) {
  std::istringstream input{pages};
  uint32_t page;
  Pages page_storage;
  while (!input.fail()) {
    input >> page;
    page_storage.push_back(page);
    if (input.get() != ',') break;
  }
  do_my_sort(page_storage);
  return page_storage[page_storage.size() / 2];
}
