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
#include <QtGui/QColor>

enum ItemDataKey : int { kItemDataKeyType = 0 };

enum ItemType : int { kItemTypeNode, kItemTypeEdge };

class Context {
 public:
  Context();

 public:
  QPen mEdgeNormalPen;
  QPen mEdgeSelectedPen;
  QBrush mEdgeLineNormalBrush;
  QBrush mEdgeLineSelectedBrush;
  QBrush mEdgeArrowNormalBrush;
  QBrush mEdgeArrowSelectedBrush;
  QFont mEdgeNormalFont;
  QFont mEdgeSelectedFont;

  // for view
  QColor mViewBackgroundColor = {53, 53, 53};

  // for node
  qreal mNodePadWL = 5;
  qreal mNodePadWR = 5;
  qreal mNodePadHT = 1;
  qreal mNodePadHB = 1;
  qreal mNodePadNameAttrs = 1;
  qreal mNodePadAttrs = 0.5;
  QColor mNodeNormalBoundarColor = {255, 255, 255};
  QColor mNodeSelectedBoundarColor = {255, 165, 0};
  QColor mNodeGradientColor0 = "gray";
  QColor mNodeGradientColor1 = {80, 80, 80};
  QColor mNodeGradientColor2 = {64, 64, 64};
  QColor mNodeGradientColor3 = {58, 58, 58};
  qreal mNodePenWidth = 1;
  qreal mNodeHoveredPenWidth = 1.5;
  QString mNodeFont = "Monospace";
  QColor mNodeFontColor = "white";
};

#endif  // GRAPH_CONTEXT_HPP_
