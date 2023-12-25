#pragma once

#include <iostream>
#include <istream>
#include <unordered_set>

#include "dfs_helper.h"
#include "link.h"

struct NodeProps {
  Node node;
  Nodes adjacents;

  NodeProps() { adjacents.reserve(20); }
  NodeProps(Node node) : node(node) { adjacents.reserve(20); }

  void buildDFS(DFSHelper& graph, Node prev) {
    graph.currentDFSInsert(node);
    for (size_t i = 0; i < adjacents.size(); i++) {
      LinkProps& link_to_next = graph.getLinkProps(Link{node, adjacents[i]});
      NodeProps& next_node = graph.getNodeProps(adjacents[i]);
      if (graph.currentDFSContains(next_node.node)) {
        continue;
      }
      link_to_next.link_used_in_dfs++;
      next_node.buildDFS(graph, node);
    }
  }
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

class Graph : DFSHelper {
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
        if (linkMap.count(link) == 0)
          linkMap.emplace(link, LinkProps{link});
        else
          std::cout << "DOes this ever happend?";
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

  NodeProps& getNodeProps(Node node) override { return nodes[node]; }
  LinkProps& getLinkProps(Link link) override { return linkMap.at(link); }
  bool currentDFSContains(Node node) override {
    return currentDFSMap.count(node) == 1;
  }
  void currentDFSInsert(Node node) override { currentDFSMap.insert(node); }

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
    for (auto& node : nodes) {
      currentDFSMap.clear();
      node.second.buildDFS(*this, node.second.node);
    }
    std::vector<std::string> kalap;
    kalap.reserve(linkMap.size());
    for (auto& link_it : linkMap) {
      LinkProps& link = link_it.second;
      kalap.push_back(link.name);
      std::cout << link.link.toString() << ": " << link.link_used_in_dfs
                << "\n";
    }
    std::cout << std::endl;
  }
};
