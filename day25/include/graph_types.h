#pragma once

#include <cstddef>
#include <cstdint>
#include <istream>
#include <vector>

class Node {
  uint32_t id;

 public:
  int read(std::istream& is) {
    uint32_t local_id = 0;
    for (uint32_t i = 0; i < 3; i++) {
      char c = is.get();
      if (!is.good() || c == '\0') {
        return -1;
      }
      local_id |= (c << (i * 8));
    }
    id = local_id;
    return 0;
  }
  uint32_t getId() { return id; }

  std::string toString() {
    std::string string_id(3, 0);
    for (uint32_t i = 0; i < 3; i++) {
      string_id[i] = id & (0xf << 8 * i);
    }
    return string_id;
  }
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

  std::string toString() { return a.toString() + b.toString(); }
};

class Graph {
  std::vector<Link> links;

 public:
  Graph() { links.reserve(1200); }
  void insert(Link node) { links.push_back(node); }

  const Link& operator[](size_t idx) const { return links[idx]; }
  const Link& at(size_t idx) const { return links[idx]; }
};
