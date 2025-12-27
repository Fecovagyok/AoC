#include "my_part2_helper.h"

#include <lemon/connectivity.h>
#include <lemon/list_graph.h>

class MyDFSVisitor : public lemon::DfsVisitor<lemon::ListDigraph> {
 public:
  typedef typename Digraph::Node Node;
  typedef typename Digraph::Arc edge;

  void leave(const Node& node) { (void)node; }
};

void kalap(Universe& universe) {
  MyDFSVisitor visitor;
  lemon::DfsVisit<lemon::ListDigraph, MyDFSVisitor> dfs(universe.graph,
                                                        visitor);
  dfs.init();
  for (lemon::ListDigraph::NodeIt it{universe.graph}; it != lemon::INVALID;
       ++it) {
    if (!dfs.reached(it)) {
      dfs.addSource(it);
      dfs.start();
    }
  }
}
