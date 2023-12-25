#pragma once

#include <iostream>
#include <istream>
#include <unordered_set>

#include "link.h"

class DFSHelper {
  virtual NodeProps& getNodeProps(Node node) = 0;
  virtual LinkProps& getLinkProps(Link link) = 0;
  virtual bool currentDFSContains(Node node) = 0;
  virtual void currentDFSInsert(Node node) = 0;
};

struct NodeProps {
  Node node;
  Nodes adjacents;

  NodeProps() { adjacents.reserve(20); }
  NodeProps(Node node) : node(node) { adjacents.reserve(20); }

  void buildDFS(DFSHelper& graph) {}

  bool operator<(const NodeProps& other) const { return node < other.node; }
  bool operator>(const NodeProps& other) const { return node > other.node; }
  bool operator==(const NodeProps& other) const { return node == other.node; }
};

namespace std {
template <>
struct hash<NodeProps> {
  size_t operator()(const NodeProps& n) const { return hash<Node>{}(n.node); }
};
}  // namespace std

struct NodeComp {
  bool operator()(Node first, Node other) { return first < other; }
};

using NodePropsCont = std::unordered_map<Node, NodeProps>;

class Graph {
  NodePropsCont nodes;
  LinkMap linkMap;
  std::unordered_set<Node> currentDFSMap;

 public:
  void readLinkMap(std::istream& is, Node key) {
    Node node;
    NodeProps& local_nodes = nodes.emplace(key, NodeProps{key}).first->second;

    while (true) {
      is.ignore(3, ' ');
      if (node.read(is)) {
        break;
      }
      // Inserting neighbours
      local_nodes.adjacents.push_back(node);
      {
        Link link{key, node};
        linkMap[link] = LinkProps{link};
      }

      // Inserting node itself
      if (nodes.count(node) == 0) {
        NodeProps& inserted =
            nodes.emplace(node, NodeProps{node}).first->second;
        inserted.adjacents.push_back(key);
      } else {
        nodes[node].adjacents.push_back(key);
      }
    }
  }

  NodeProps& getNodeProps(Node node) { return nodes[node]; }
  LinkProps& getLinkProps(Link link) { return linkMap[link]; }
  bool currentDFSContains(Node node) { return currentDFSMap.count(node) == 1; }
  void currentDFSInsert(Node node) { currentDFSMap.insert(node); }

  void selfTest() {
    if (nodes.size() != 15) {
      std::cout << "Nem 15" << std::endl;
      exit(1);
    }
    std::unordered_set<Node> set;
    for (const auto& node : nodes) {
      set.clear();
      const Nodes& node_ids = node.second.adjacents;
      for (size_t i = 0; i < node_ids.size(); i++) {
        if (set.count(node_ids[i]) == 1) {
          std::cout << "Baj"
                    << "\n";
        }
        set.insert(node_ids[i]);
      }
    }
  }

  void dfs() {
    currentDFSMap.clear();
    for (auto& node : nodes) {
      nodes[node.second.adjacents[0]];
    }
  }
};
