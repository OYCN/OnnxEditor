/**
 * @file context.hpp
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

#ifndef GRAPH_CONTEXT_HPP_
#define GRAPH_CONTEXT_HPP_

#include <QtGui/QPainter>

enum ItemDataKey : int { kItemDataKeyType = 0 };

enum ItemType : int { kItemTypeNode, kItemTypeEdge };

class Context {
 public:
  Context();

 public:
  QPen mNodeNormalPen;
  QPen mNodeSelectedPen;
  QPen mEdgeNormalPen;
  QPen mEdgeSelectedPen;

  QBrush mNodeNormalBrush;
  QBrush mNodeSelectedBrush;
  QBrush mEdgeLineNormalBrush;
  QBrush mEdgeLineSelectedBrush;
  QBrush mEdgeArrowNormalBrush;
  QBrush mEdgeArrowSelectedBrush;

  QFont mNodeNormalFont;
  QFont mNodeSelectedFont;
  QFont mEdgeNormalFont;
  QFont mEdgeSelectedFont;
};

#endif  // GRAPH_CONTEXT_HPP_
