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

#include <QtCore/QDebug>
#include <QtGui/QPainter>

GraphNode::GraphNode(Context &ctx, QString name) : mCtx(ctx), mName(name) {
  setData(kItemDataKeyType, kItemTypeNode);
  setFlag(QGraphicsItem::ItemIsSelectable, true);
  setAcceptHoverEvents(true);
  updateAll();
}

QRectF GraphNode::boundingRect() const { return mAllRect; }

void GraphNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                      QWidget *) {
  painter->save();

  // for rect
  {
    auto color = isSelected() ? mCtx.mNodeSelectedBoundarColor
                              : mCtx.mNodeNormalBoundarColor;
    auto width = mHovered ? mCtx.mNodeHoveredPenWidth : mCtx.mNodePenWidth;
    QPen p(color, width);
    painter->setPen(p);
    QLinearGradient gradient(QPointF(0.0, 0.0),
                             QPointF(2.0, mAllRect.height()));
    gradient.setColorAt(0.0, mCtx.mNodeGradientColor0);
    gradient.setColorAt(0.03, mCtx.mNodeGradientColor1);
    gradient.setColorAt(0.97, mCtx.mNodeGradientColor2);
    gradient.setColorAt(1.0, mCtx.mNodeGradientColor3);
    painter->setBrush(gradient);
    painter->drawRoundedRect(mAllRect, 3, 3);
  }

  // for name
  {
    QFont f(mCtx.mNodeFont);
    f.setBold(true);
    painter->setFont(f);
    painter->setPen(mCtx.mNodeFontColor);
    painter->drawText(mNameRect, Qt::AlignCenter, mName);
  }

  // for attrs
  {
    QFont f(mCtx.mNodeFont);
    painter->setFont(f);
    painter->setPen(mCtx.mNodeFontColor);
    QRectF this_attr_rect = mFirstAttrRect;
    for (const auto &str : mAttrsStr) {
      painter->drawText(this_attr_rect, Qt::AlignCenter, str);
      this_attr_rect.translate(0, mCtx.mNodePadAttrs + this_attr_rect.height());
    }
  }

  painter->restore();
}

void GraphNode::updateAll() {
  QFont name_font(mCtx.mNodeFont);
  name_font.setBold(true);
  QFontMetrics name_fm(name_font);
  QFont attrs_font(mCtx.mNodeFont);
  QFontMetrics attr_fm(attrs_font);
  QRectF name_rect = name_fm.boundingRect(mName);
  QString max_len_attr;
  auto attrs = mAttrs.keys();
  mAttrsStr.clear();
  for (const auto &k : attrs) {
    QString this_str = k + ": " + mAttrs[k];
    mAttrsStr.append(this_str);
    if (this_str.size() > max_len_attr.size()) {
      max_len_attr = this_str;
    }
  }
  QRectF attr_rect = attr_fm.boundingRect(max_len_attr);
  auto w = name_rect.width();
  auto h = name_rect.height();
  if (w < attr_rect.width()) w = attr_rect.width();
  if (attrs.size() > 0) {
    h += attr_rect.height() * attrs.size() + mCtx.mNodePadNameAttrs +
         mCtx.mNodePadAttrs * (attrs.size() - 1);
  }
  mAllRect.setX(0);
  mAllRect.setY(0);
  mAllRect.setWidth(w + mCtx.mNodePadWL + mCtx.mNodePadWR);
  mAllRect.setHeight(h + mCtx.mNodePadHT + mCtx.mNodePadHB);
  mNameRect.setX((mAllRect.width() - name_rect.width()) / 2);
  mNameRect.setY(mCtx.mNodePadHT);
  mNameRect.setWidth(name_rect.width());
  mNameRect.setHeight(name_rect.height());
  mFirstAttrRect.setX(mCtx.mNodePadWL);
  mFirstAttrRect.setY(mCtx.mNodePadHT + name_rect.height() +
                      mCtx.mNodePadNameAttrs);
  mFirstAttrRect.setWidth(attr_rect.width());
  mFirstAttrRect.setHeight(attr_rect.height());
  update();
}

void GraphNode::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
  // qDebug() << "Enter hover";
  mHovered = true;
  update();
}

void GraphNode::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
  // qDebug() << "Leave hover";
  mHovered = false;
  update();
}
