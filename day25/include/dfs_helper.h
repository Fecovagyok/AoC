#pragma once

#include <cstdint>

struct NodeProps;
struct LinkProps;
class Node;
class Link;

class DFSHelper {
 public:
  virtual NodeProps& getNodeProps(Node node) = 0;
  virtual LinkProps& getLinkProps(Link link) = 0;
  virtual uint64_t getTime() = 0;
  virtual void incTime() = 0;
};
