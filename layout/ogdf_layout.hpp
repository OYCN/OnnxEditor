/**
 * @file ogdf_layout.hpp
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

#ifndef LAYOUT_OGDF_LAYOUT_HPP_
#define LAYOUT_OGDF_LAYOUT_HPP_

#include <ogdf/basic/Graph.h>

#include "layout.hpp"

namespace layout {

class OgdfLayout : public Layout {
 public:
  Node_t* addNodeImpl(Node_t* node) override;
  Edge_t* addEdgeImpl(Edge_t* edge) override;
  void layoutImpl() override;

 private:
  ogdf::Graph mGraph;
};

}  // namespace layout

#endif  // LAYOUT_OGDF_LAYOUT_HPP_
