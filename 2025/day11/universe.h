#pragma once

#include <lemon/list_graph.h>
#include <me_split.h>

#include <cstdint>
#include <string_view>

#define START_NODE_STR "svr"
#define END_NODE_STR "out"

struct MyNodeKey {
  char node_id[4] = {};
  uint32_t asInteger() const {
    return *(reinterpret_cast<const uint32_t*>(node_id));
  }
  MyNodeKey() {}
  MyNodeKey(const std::string_view str) { memcpy(node_id, str.data(), 3); }
  MyNodeKey(const char* str) { memcpy(node_id, str, 3); }
  bool operator==(const MyNodeKey other) const {
    return memcmp(node_id, other.node_id, 3) == 0;
  }
  const std::string_view toStringView() const {
    return std::string_view{node_id, 3};
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
  std::unique_ptr<lemon::ListDigraph::NodeMap<MyNodeKey>> inverse_map;

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
    std::vector<std::string_view> link_ends = split(line_view.substr(pos + 2));
    if (node_str == END_NODE_STR) {
      return;
    }
    for (size_t i = 0; i < link_ends.size(); i++) {
      std::string_view link_view = link_ends[i];
      if (link_view == START_NODE_STR) {
        return;
      }
    }
    MyNodeKey key{node_str};
    GraphNode node = toGraphNode(key);
    for (size_t i = 0; i < link_ends.size(); i++) {
      GraphNode targetNode = toGraphNode({link_ends[i]});
      graph.addArc(node, targetNode);
    }
  }

  void createInverseMap() {
    inverse_map =
        std::make_unique<lemon::ListDigraph::NodeMap<MyNodeKey>>(this->graph);

    for (const auto iter : nodeMap) {
      lemon::ListDigraph::NodeIt graphIter{graph, iter.second};
      inverse_map->set(graphIter, iter.first);
    }
  }
};
