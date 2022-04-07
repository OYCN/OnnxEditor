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

#include <ogdf/layered/MedianHeuristic.h>
#include <ogdf/layered/OptimalHierarchyLayout.h>
#include <ogdf/layered/OptimalRanking.h>
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
  std::cout << "link " << node1 << " to " << node2 << std::endl;
  ogdf::EdgeElement* e = mGraph.newEdge(node1, node2);
  edge->mHandle = e;
  return edge;
}
void OgdfLayout::layoutImpl() {
  ogdf::GraphAttributes graphAttr(mGraph,
                                  ogdf::GraphAttributes::nodeGraphics |
                                      ogdf::GraphAttributes::edgeGraphics);
  for (const auto& node : mNodes) {
    auto handle = std::any_cast<ogdf::NodeElement*>(node.mHandle);
    graphAttr.width(handle) = node.mW;
    graphAttr.height(handle) = node.mH;
    std::cout << "Add node w=" << node.mW << " h=" << node.mH << std::endl;
  }
  ogdf::SugiyamaLayout layout;
  layout.setRanking(new ogdf::OptimalRanking);
  layout.setCrossMin(new ogdf::MedianHeuristic);
  ogdf::OptimalHierarchyLayout* ohl = new ogdf::OptimalHierarchyLayout;
  ohl->layerDistance(30.0);
  ohl->nodeDistance(25.0);
  ohl->weightBalancing(0.8);
  layout.setLayout(ohl);
  layout.call(graphAttr);

  for (auto& node : mNodes) {
    auto handle = std::any_cast<ogdf::NodeElement*>(node.mHandle);
    node.mX = graphAttr.x(handle);
    node.mY = graphAttr.y(handle);
    std::cout << "Layout x=" << node.mX << " y=" << node.mY << std::endl;
  }
}

}  // namespace layout
