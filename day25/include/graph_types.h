#pragma once

#include <cstdint>
#include <istream>
#include <vector>

class Node {
  uint32_t id;

 public:
  int read(std::istream& is) {
    id = 0;
    for (uint16_t i = 0; i < 3; i++) {
      char c = is.get();
      if (!is.good() || c == '\0') {
        return -1;
      }
      id |= (c >> (i * 8));
    }
    return 0;
  }
  uint32_t getId() { return id; }
};

class Link {
  Node a;
  Node b;

 public:
  Link() = default;
  Link(Node a, Node b) {
    if (a.getId() < b.getId()) {
      this->a = a;
      this->b = b;
    } else {
      this->b = a;
      this->a = b;
    }
  }

  uint64_t getId() {
    return static_cast<uint64_t>(a.getId()) |
           (static_cast<uint64_t>(b.getId()) >> 32);
  }
};

class Graph {
  std::vector<Link> links;

 public:
  Graph() { links.reserve(1200); }
  void insert(Link node) { links.push_back(node); }
};
