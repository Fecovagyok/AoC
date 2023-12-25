#include <cstdint>
#include <map>
#include <unordered_map>

#include "node.h"

class Link {
  Node a;
  Node b;

 public:
  Link(Node a, Node b) {
    if (a.getId() < b.getId()) {
      this->a = a;
      this->b = b;
    } else {
      this->b = a;
      this->a = b;
    }
  }

  uint64_t getId() const {
    return static_cast<uint64_t>(a.getId()) |
           (static_cast<uint64_t>(b.getId()) << 32);
  }

  bool operator==(Link other) const { return getId() == other.getId(); }
  std::string toString() { return a.toString() + ' ' + b.toString(); }
  Node getA() const { return a; }
  Node getB() const { return b; }
};

namespace std {
template <>
struct hash<Link> {
  size_t operator()(Link l) const { return hash<uint64_t>{}(l.getId()); }
};
}  // namespace std

struct LinkComp {
  bool operator()(Link first, Link other) {
    return first.getA() < other.getA();
  }
};

struct LinkProps {
  Link link;
  uint64_t link_used_in_dfs = 0;
  std::string name;
  LinkProps(Link link) : link(link), name(link.toString()) {}
};

using LinkMap = std::unordered_map<Link, LinkProps>;
