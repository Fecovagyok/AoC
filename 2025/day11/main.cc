#include <lemon/connectivity.h>
#include <lemon/core.h>
#include <lemon/list_graph.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <memory>
#include <string_view>
#include <unordered_map>

#include "aoc_reader.h"
#include "me_split.h"

// class MyNodeMap {
//   std::vector<lemon::ListDigraph::Node> map;

//  public:
//   void set(lemon::ListDigraph::NodeIt key, lemon::ListDigraph::Node value) {
//     if (key >= map.size()) {
//       map.reserve(key + 1);
//       for (size_t i = 0; i < key - map.size() + 1; i++) {
//         map.emplace_back();
//       }
//       map[key] = value;
//     };
//   }

//   lemon::ListDigraph::Node operator[](size_t key) const { return map.at(key);
//   }
// };

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
    if (node_str == "out") {
      return;
    }
    for (size_t i = 0; i < link_ends.size(); i++) {
      std::string_view link_view = link_ends[i];
      if (link_view == "you") {
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

int main() {
  Universe universe;
  auto cb = [&universe](std::string& line) { universe.parse(line); };
  AoCReader reader{cb, 512, "2025/day11/input.txt"};
  reader.read();
  universe.createInverseMap();
  lemon::ListDigraph::NodeMap<int> nodes_order{universe.graph};
  if (!lemon::checkedTopologicalSort(universe.graph, nodes_order)) {
    std::cerr << "Baj" << std::endl;
  }

  std::vector<lemon::ListDigraph::NodeIt> topologicalSorted(
      universe.nodeMap.size(), lemon::INVALID);

  for (lemon::ListDigraph::NodeIt i{universe.graph}; i != lemon::INVALID; ++i) {
    size_t order = nodes_order[i];
    topologicalSorted[order] = i;
  }

  lemon::ListDigraph::Node start = universe.nodeMap["you"];
  lemon::ListDigraph::NodeMap<uint64_t> distinctPathMap(universe.graph, 0);
  distinctPathMap[start] = 1;
  for (auto current_vertex : topologicalSorted) {
    for (lemon::ListDigraph::OutArcIt arc{universe.graph, current_vertex};
         arc != lemon::INVALID; ++arc) {
      auto other_end_vertex = universe.graph.target(arc);
      distinctPathMap[other_end_vertex] += distinctPathMap[current_vertex];
    }
  }

  lemon::ListDigraph::Node end = universe.nodeMap["out"];
  std::cout << distinctPathMap[end] << std::endl;
}
