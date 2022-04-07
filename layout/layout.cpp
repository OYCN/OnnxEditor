/**
 * @file layout.cpp
 * @brief 
 * @author oPluss (opluss@qq.com)
 * 
 * @copyright Copyright (c) 2022  oPluss
 * 
 * @par Modify log:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2022-04-07 <td>1.0     <td>oPluss     <td>Initial
 * </table>
 */

#include <utility>
#include <cassert>

#include "layout.hpp"

#include "ogdf_layout.hpp"

namespace layout {

Node_t* Layout::addNode(double w, double h) {
  Node_t n;
  n.mW = w;
  n.mH = h;
  mNodes.emplace_back(n);
  return addNodeImpl(&mNodes.back());
}

Edge_t* Layout::addEdge(Node_t* from, Node_t* to) {
  assert (from != nullptr);
  assert (to != nullptr);
  Edge_t e;
  e.mFrom = from;
  e.mTo = to;
  mEdges.emplace_back(e);
  return addEdgeImpl(&mEdges.back());
}

void Layout::layout() { layoutImpl(); }

Node_t* Layout::addNodeImpl(Node_t* node) { return node; }

Edge_t* Layout::addEdgeImpl(Edge_t* edge) { return edge; }

void Layout::layoutImpl() { return; }

std::unique_ptr<Layout> getLayoutEngine(LayoutEngine type) {
  Layout* ptr = nullptr;
  switch (type) {
    case kNone:
      ptr = new Layout();
      break;
    case kOGDF:
      ptr = new OgdfLayout();
      break;
    default:
      std::abort();
  }
  return std::move(std::unique_ptr<Layout>(ptr));
}

}  // namespace layout
