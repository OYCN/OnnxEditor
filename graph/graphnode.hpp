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

#include <QtCore/QMap>
#include <QtWidgets/QGraphicsItem>

#include "context.hpp"

class GraphNode : public QGraphicsItem {
 public:
  explicit GraphNode(Context &ctx, QString name);

  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = 0) override;

  void updateAll();

 public:
  QString getName() const { return mName; }
  void setName(QString name) { mName = name; }

  QMap<QString, QString> getAttrs() const { return mAttrs; }
  QString getAttr(QString key) const { return mAttrs.value(key); }
  void setAttr(QString key, QString value) { mAttrs[key] = value; }

 protected:
  void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
  void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

 private:
  Context &mCtx;

  bool mHovered = false;

  QString mName = "";
  QMap<QString, QString> mAttrs;
  QList<QString> mAttrsStr;

  QRectF mAllRect;
  QRectF mNameRect;
  QRectF mFirstAttrRect;
};

#endif  // GRAPH_GRAPHNODE_HPP_
