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
  QPen mNodeNormalNamePen;
  QPen mNodeSelectedNamePen;
  QPen mNodeNormalAttrsPen;
  QPen mNodeSelectedAttrsPen;
  QPen mEdgeNormalPen;
  QPen mEdgeSelectedPen;

  QBrush mNodeNormalNameBrush;
  QBrush mNodeSelectedNameBrush;
  QBrush mNodeNormalAttrsBrush;
  QBrush mNodeSelectedAttrsBrush;
  QBrush mEdgeLineNormalBrush;
  QBrush mEdgeLineSelectedBrush;
  QBrush mEdgeArrowNormalBrush;
  QBrush mEdgeArrowSelectedBrush;

  QFont mNodeNormalNameFont;
  QFont mNodeSelectedNameFont;
  QFont mNodeNormalAttrsFont;
  QFont mNodeSelectedAttrsFont;
  QFont mEdgeNormalFont;
  QFont mEdgeSelectedFont;

  qreal mNodePadWL = 5;
  qreal mNodePadWR = 5;
  qreal mNodePadHT = 1;
  qreal mNodePadHB = 1;
  qreal mNodePadNameAttrs = 1;
  qreal mNodePadAttrs = 0.5;
};

#endif  // GRAPH_CONTEXT_HPP_
