#pragma once

class NodeProps;
class LinkProps;
class Node;
class Link;

class DFSHelper {
 public:
  virtual NodeProps& getNodeProps(Node node) = 0;
  virtual LinkProps& getLinkProps(Link link) = 0;
  virtual bool currentDFSContains(Node node) = 0;
  virtual void currentDFSInsert(Node node) = 0;
};
