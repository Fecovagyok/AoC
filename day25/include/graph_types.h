#pragma once

#include <cstddef>
#include <cstdint>
#include <istream>
#include <map>
#include <vector>

#include "link.h"

class Graph {
  std::vector<Link> links;
  std::map<Node, Nodes> link_map;

 public:
  Graph() { links.reserve(1200); }
  void insert(Link node) { links.push_back(node); }

  void read(std::istream& is) {}

  const Link& operator[](size_t idx) const { return links[idx]; }
  const Link& at(size_t idx) const { return links[idx]; }
};
