#include <cstdlib>
#include <ios>
#include <iostream>
#include <sstream>

#include "aoc_reader.h"
#include "graph_types.h"

#define INPUT_FILE "input.txt"

int main() {
  Graph graph;
  auto process_line = [&graph](std::string& buf) {
    std::istringstream is{buf};
    Node first;
    if (first.read(is)) {
      std::cout << "Baj oreg" << std::endl;
      exit(1);
    }
    is.ignore(1, ':');
    while (is.good()) {
      graph.readLinkMap(is, first);
    }
  };

  AoCReader reader{process_line, 270, "./day25/" INPUT_FILE};
  reader.read();
  graph.dfs();

  return 0;
}
