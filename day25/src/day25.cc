#include <cstdlib>
#include <ios>
#include <iostream>
#include <sstream>

#include "aoc_reader.h"
#include "graph_types.h"

#define INPUT_FILE "example.txt"

int main() {
  std::ios_base::sync_with_stdio(false);
  Graph graph;
  auto process_line = [&graph](std::string& buf) {
    std::istringstream is{buf};
    Node first;
    if (!first.read(is)) {
      std::cout << "Baj oreg" << std::endl;
      exit(1);
    }
    is.ignore(1, ':');
    while (true) {
      is.ignore(1, ' ');
      Node other;
      if (!other.read(is)) {
        break;
      }
      graph.insert(Link{first, other});
    }
  };

  AoCReader reader{process_line, 270, "./day25/" INPUT_FILE};

  reader.read();
  return 0;
}
