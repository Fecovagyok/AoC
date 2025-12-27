#include <lemon/connectivity.h>
#include <lemon/core.h>
#include <lemon/list_graph.h>

#include <cstddef>
#include <cstdint>
#include <cstring>

#include "aoc_reader.h"
#include "universe.h"

int main() {
  Universe universe;
  auto cb = [&universe](std::string& line) { universe.parse(line); };
  AoCReader reader{cb, 512, "2025/day11/input2.txt"};
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

  lemon::ListDigraph::Node start = universe.nodeMap[START_NODE_STR];
  lemon::ListDigraph::NodeMap<uint64_t> distinctPathMap(universe.graph, 0);
  distinctPathMap[start] = 1;
  for (auto current_vertex : topologicalSorted) {
    for (lemon::ListDigraph::OutArcIt arc{universe.graph, current_vertex};
         arc != lemon::INVALID; ++arc) {
      auto other_end_vertex = universe.graph.target(arc);
      distinctPathMap[other_end_vertex] += distinctPathMap[current_vertex];
    }
  }

  lemon::ListDigraph::Node end = universe.nodeMap[END_NODE_STR];
  std::cout << distinctPathMap[end] << std::endl;
}
