/**
 * @file graphedge.hpp
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

#ifndef GRAPH_GRAPHEDGE_HPP_
#define GRAPH_GRAPHEDGE_HPP_

#include <QtWidgets/QGraphicsItem>

#include "context.hpp"

class GraphNode;

class GraphEdge : public QGraphicsItem {
 public:
  explicit GraphEdge(Context& ctx, GraphNode* from, GraphNode* to,
                     QString name = "");

  void updateAll();

 public:
  QRectF boundingRect() const;
  QPainterPath shape() const;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
             QWidget* widget = 0);

  GraphNode* getFrom() const { return mFrom; }
  GraphNode* getTo() const { return mTo; }
  void setFrom(GraphNode* node) { mFrom = node; }
  void setTo(GraphNode* node) { mTo = node; }

 private:
  Context& mCtx;

  QString mName;

  GraphNode* mFrom;
  GraphNode* mTo;

  QPointF mStart;
  QPointF mStop;
  QPointF mText;

  QPainterPath mPath;
  QRectF mNameRect;
  QPolygonF mArrow;
};

#endif  // GRAPH_GRAPHEDGE_HPP_
