#include <lemon/connectivity.h>
#include <lemon/core.h>
#include <lemon/list_graph.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>

#include "aoc_reader.h"
#include "universe.h"

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

  lemon::ListDigraph::Node start = universe.nodeMap[START_NODE_STR];
  lemon::ListDigraph::NodeMap<std::array<uint64_t, 4>> distinctPathMap(
      universe.graph, {0, 0, 0, 0});

  const lemon::ListDigraph::Node dac_node = universe.nodeMap["dac"];
  const lemon::ListDigraph::Node fft_node = universe.nodeMap["fft"];
  enum TraverseState : size_t {
    SEEN_NOTHING = 0,
    SEEN_DAC = 1,
    SEEN_FFT = 2,
    SEEN_BOTH = SEEN_DAC | SEEN_FFT,
    TRAVERSE_STATE_MAX = 4
  };

  distinctPathMap[start][SEEN_NOTHING] = 1;
  for (auto current_vertex : topologicalSorted) {
    for (size_t i = 0; i < TRAVERSE_STATE_MAX; i++) {
      uint64_t been_reached_this_way = distinctPathMap[current_vertex][i];
      if (been_reached_this_way == 0) continue;
      for (lemon::ListDigraph::OutArcIt arc{universe.graph, current_vertex};
           arc != lemon::INVALID; ++arc) {
        auto other_end_vertex = universe.graph.target(arc);
        size_t other_vertex_state = i;
        if (other_end_vertex == dac_node) {
          other_vertex_state |= SEEN_DAC;
        }
        if (other_end_vertex == fft_node) {
          other_vertex_state |= SEEN_FFT;
        }
        distinctPathMap[other_end_vertex][other_vertex_state] +=
            been_reached_this_way;
      }
    }
  }

  lemon::ListDigraph::Node end = universe.nodeMap[END_NODE_STR];
  std::cout << distinctPathMap[end][SEEN_BOTH] << std::endl;
}
