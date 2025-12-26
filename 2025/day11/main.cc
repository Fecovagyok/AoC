#include <lemon/connectivity.h>
#include <lemon/list_graph.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string_view>
#include <unordered_map>

#include "aoc_reader.h"
#include "me_split.h"

struct MyNodeKey {
  char node_id[4] = {};
  uint32_t asInteger() const {
    return *(reinterpret_cast<const uint32_t*>(node_id));
  }
  MyNodeKey(const std::string_view str) { memcpy(node_id, str.data(), 3); }
  bool operator==(const MyNodeKey other) const {
    return memcmp(node_id, other.node_id, 3) == 0;
  }
};

namespace std {
template <>
struct hash<MyNodeKey> {
  uint32_t operator()(const MyNodeKey node) const noexcept {
    return node.asInteger();
  }
};
}  // namespace std

struct Universe {
  lemon::ListDigraph graph;
  using GraphNode = lemon::ListDigraph::Node;
  std::unordered_map<MyNodeKey, GraphNode> nodeMap;

  GraphNode toGraphNode(MyNodeKey key) {
    GraphNode node;
    if (nodeMap.contains(key)) {
      node = nodeMap[key];
    } else {
      node = graph.addNode();
      nodeMap[key] = node;
    }
    return node;
  }

  void parse(std::string& line) {
    const std::string_view line_view{line};
    size_t pos = line_view.find_first_of(':');
    std::string_view node_str = line_view.substr(0, pos);
    MyNodeKey key{node_str};
    GraphNode node = toGraphNode(key);
    std::vector<std::string_view> link_ends = split(line_view.substr(pos + 2));
    for (size_t i = 0; i < link_ends.size(); i++) {
      GraphNode targetNode = toGraphNode({link_ends[i]});
      graph.addArc(node, targetNode);
    }
  }
};

int main() {
  Universe universe;
  auto cb = [&universe](std::string& line) { universe.parse(line); };
  AoCReader reader{cb, 512, "2025/day11/input.txt"};
  reader.read();
}
