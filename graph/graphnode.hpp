/**
 * @file graphnode.hpp
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

#ifndef GRAPH_GRAPHNODE_HPP_
#define GRAPH_GRAPHNODE_HPP_

#include <QtWidgets/QGraphicsItem>

#include "context.hpp"

class GraphNode : public QGraphicsItem {
 public:
  explicit GraphNode(Context &ctx, QString name);

  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = 0) override;

  QString getName() const { return mName; }

 private:
  Context &mCtx;
  QString mName = "";
};

#endif  // GRAPH_GRAPHNODE_HPP_
