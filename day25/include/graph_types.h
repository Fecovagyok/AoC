#pragma once

#include <istream>
#include <unordered_set>

#include "link.h"

class Graph {
  std::unordered_set<NodeProps> nodes;
  LinkMap linkMap;

 public:
  Graph() { linkMap.setNodeProps(&nodes); }
  void readLinkMap(std::istream &is, Node key) {
    Node node;
    NodeProps local_nodes;
    nodes.emplace(key);

    while (true) {
      if (node.read(is)) {
        break;
      }
      local_nodes.adjacents.push_back(node);
      if (nodes.count(node) == 0) {
        nodes.emplace(key);
      }
    }
    linkMap[key] = std::move(local_nodes);
  }

  void dfs() {}
};
