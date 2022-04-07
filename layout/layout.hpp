/**
 * @file layout.hpp
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

#ifndef LAYOUT_COMMON_HPP_
#define LAYOUT_COMMON_HPP_

#include <any>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace layout {

struct Node_t {
  Node_t(double w, double h) : mW(w), mH(h) {}
  double mW = 0;
  double mH = 0;
  double mX = 0;
  double mY = 0;
  std::any mHandle;
  std::map<std::string, std::any> mData;
};

struct Edge_t {
  Edge_t(Node_t* f, Node_t* t) : mFrom(f), mTo(t) {}
  Node_t* mFrom = nullptr;
  Node_t* mTo = nullptr;
  std::any mHandle;
  std::map<std::string, std::any> mData;
};

enum LayoutEngine : int {
  kNone,
  kOGDF,
};

class Layout {
 public:
  virtual ~Layout() {}
  Node_t* addNode(double w, double h);
  Edge_t* addEdge(Node_t* from, Node_t* to);
  void layout();

 protected:
  virtual Node_t* addNodeImpl(Node_t* node);
  virtual Edge_t* addEdgeImpl(Edge_t* edge);
  virtual void layoutImpl();

 protected:
  std::vector<Node_t> mNodes;
  std::vector<Edge_t> mEdges;
};

std::unique_ptr<Layout> getLayoutEngine(LayoutEngine type);

}  // namespace layout

#endif  // LAYOUT_COMMON_HPP_
