#pragma once

#include <istream>
#include <map>
#include <unordered_set>

#include "link.h"

class Graph {
  std::unordered_set<NodeProps> nodes;
  LinkMap linkMap;

 public:
  void readLinkMap(std::istream& is, Node key) {
    Node node;
    NodeProps local_nodes;
    NodeProps eNode{node};
    nodes.insert(std::move(eNode));
    while (true) {
      if (node.read(is)) {
        break;
      }
      local_nodes.adjacents.push_back(node);
    }
    linkMap[key] = std::move(local_nodes);
  }

  void dfs() {}
};
