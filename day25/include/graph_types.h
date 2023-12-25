#pragma once

#include <cstddef>
#include <cstdint>
#include <istream>
#include <map>
#include <vector>

#include "link.h"

class Graph {
  std::vector<Link> links;
  LinkMap linkMap;

 public:
  Graph() { links.reserve(1200); }
  void insert(Link node) { links.push_back(node); }

  void readLinkMap(std::istream& is, Node key) {
    Node node;
    Nodes nodes;
    nodes.reserve(8);
    while (true) {
      if (node.read(is)) {
        break;
      }
      nodes.push_back(node);
    }
    linkMap[node] = std::move(nodes);
  }

  const Link& operator[](size_t idx) const { return links[idx]; }
  const Link& at(size_t idx) const { return links[idx]; }
};
