#include <cstdint>
#include <istream>
#include <unordered_map>
#include <vector>

#include "dfs_helper.h"

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
  uint32_t getId() const { return id; }

  std::string toString() const {
    std::string string_id(3, 0);
    for (uint32_t i = 0; i < 3; i++) {
      string_id[i] = (id >> i * 8) & 0xff;
    }
    return string_id;
  }

  bool operator<(Node other) const { return this->id < other.id; }
  bool operator>(Node other) const { return this->id > other.id; }
  bool operator==(Node other) const { return id == other.id; }
};

typedef std::vector<Node> Nodes;

namespace std {
template <>
struct hash<Node> {
  size_t operator()(Node n) const { return hash<uint32_t>{}(n.getId()); }
};
}  // namespace std

struct NodeComp {
  bool operator()(Node first, Node other) { return first < other; }
};

using NodePropsCont = std::unordered_map<Node, NodeProps>;
