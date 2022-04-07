/**
 * @file graphnode.cpp
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

#include "graphnode.hpp"

#include <QtGui/QPainter>

GraphNode::GraphNode(Context &ctx, QString name) : mCtx(ctx), mName(name) {
  setData(kItemDataKeyType, kItemTypeNode);
  setFlag(QGraphicsItem::ItemIsSelectable, true);
}

QRectF GraphNode::boundingRect() const {
  QFont *font;
  if (isSelected()) {
    font = &mCtx.mNodeSelectedFont;
  } else {
    font = &mCtx.mNodeNormalFont;
  }

  QFontMetrics fm(*font);
  QRectF rect = fm.boundingRect(mName);
  float dx = rect.width() * 0.05;
  float dy = rect.height() * 0.05;
  dx = dx >= 2 ? dx : 2;
  dy = dy >= 1 ? dy : 1;
  //    qDebug() << dx << dy;
  rect.adjust(-dx, -dy, 2 * dx, 2 * dy);
  //    qDebug() << rect;
  return rect;
}

void GraphNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                      QWidget *) {
  painter->save();

  if (isSelected()) {
    painter->setPen(mCtx.mNodeSelectedPen);
    painter->setBrush(mCtx.mNodeSelectedBrush);
    painter->setFont(mCtx.mNodeSelectedFont);
  } else {
    painter->setPen(mCtx.mNodeNormalPen);
    painter->setBrush(mCtx.mNodeNormalBrush);
    painter->setFont(mCtx.mNodeNormalFont);
  }

  auto rect = boundingRect();
  painter->drawRoundedRect(rect, 3, 3);
  painter->drawText(rect, Qt::AlignCenter, mName);

  painter->restore();
}
