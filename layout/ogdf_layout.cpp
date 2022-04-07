/**
 * @file ogdf_layout.cpp
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

#include "ogdf_layout.hpp"

#include <ogdf/layered/FastHierarchyLayout.h>
#include <ogdf/layered/SugiyamaLayout.h>

namespace layout {

Node_t* OgdfLayout::addNodeImpl(Node_t* node) {
  ogdf::NodeElement* n = mGraph.newNode();
  node->mHandle = n;
  return node;
}
Edge_t* OgdfLayout::addEdgeImpl(Edge_t* edge) {
  auto node1 = std::any_cast<ogdf::NodeElement*>(edge->mFrom->mHandle);
  auto node2 = std::any_cast<ogdf::NodeElement*>(edge->mTo->mHandle);
  ogdf::EdgeElement* e = mGraph.newEdge(node1, node2);
  edge->mHandle = e;
  return edge;
}
void OgdfLayout::layoutImpl() {
  ogdf::GraphAttributes graphAttr(mGraph,
                                  ogdf::GraphAttributes::nodeGraphics |
                                      ogdf::GraphAttributes::edgeGraphics |
                                      ogdf::GraphAttributes::nodeLabel |
                                      ogdf::GraphAttributes::edgeStyle |
                                      ogdf::GraphAttributes::nodeStyle |
                                      ogdf::GraphAttributes::nodeTemplate);
  for (const auto& node : mNodes) {
    auto handle = std::any_cast<ogdf::NodeElement*>(node.mHandle);
    auto w = node.mW;
    auto h = node.mH;
    graphAttr.width(handle) = w;
    graphAttr.height(handle) = h;
  }
  ogdf::SugiyamaLayout layout;
  ogdf::FastHierarchyLayout* ohl = new ogdf::FastHierarchyLayout;
  ohl->layerDistance(30);
  ohl->nodeDistance(25);
  layout.setLayout(ohl);

  layout.call(graphAttr);

  for (auto& node : mNodes) {
    auto handle = std::any_cast<ogdf::NodeElement*>(node.mHandle);
    node.mX = graphAttr.x(handle);
    node.mY = graphAttr.y(handle);
  }
}

}  // namespace layout
