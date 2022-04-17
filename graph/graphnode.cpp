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
  updateAll();
}

QRectF GraphNode::boundingRect() const {
  return mAllRect;
}

void GraphNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                      QWidget *) {
  painter->save();

  // for name
  if (isSelected()) {
    painter->setPen(mCtx.mNodeSelectedNamePen);
    painter->setBrush(mCtx.mNodeSelectedNameBrush);
    painter->setFont(mCtx.mNodeSelectedNameFont);
  } else {
    painter->setPen(mCtx.mNodeNormalNamePen);
    painter->setBrush(mCtx.mNodeNormalNameBrush);
    painter->setFont(mCtx.mNodeNormalNameFont);
  }
  
  painter->drawRoundedRect(mAllRect, 3, 3);

  painter->drawText(mNameRect, Qt::AlignCenter, mName);

  // for name
  if (isSelected()) {
    painter->setPen(mCtx.mNodeSelectedAttrsPen);
    painter->setBrush(mCtx.mNodeSelectedAttrsBrush);
    painter->setFont(mCtx.mNodeSelectedAttrsFont);
  } else {
    painter->setPen(mCtx.mNodeNormalAttrsPen);
    painter->setBrush(mCtx.mNodeNormalAttrsBrush);
    painter->setFont(mCtx.mNodeNormalAttrsFont);
  }

  QRectF this_attr_rect = mFirstAttrRect;
  for (const auto& str : mAttrsStr) {
    painter->drawText(this_attr_rect, Qt::AlignCenter, str);
    this_attr_rect.translate(0, mCtx.mNodePadAttrs);
  }

  painter->restore();
}

void GraphNode::updateAll() {
  QFont name_font;
  QFont attrs_font;
  if (isSelected()) {
    name_font = mCtx.mNodeSelectedNameFont;
    attrs_font = mCtx.mNodeSelectedAttrsFont;
  } else {
    name_font = mCtx.mNodeNormalNameFont;
    attrs_font = mCtx.mNodeNormalAttrsFont;
  }

  QFontMetrics name_fm(name_font);
  QFontMetrics attr_fm(attrs_font);
  QRectF name_rect = name_fm.boundingRect(mName);
  QString max_len_attr;
  auto attrs = mAttrs.keys();
  mAttrsStr.clear();
  for (const auto& k : attrs) {
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
    h += attr_rect.height() + mCtx.mNodePadNameAttrs + mCtx.mNodePadAttrs * (attrs.size() - 1);
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
  mFirstAttrRect.setY(mCtx.mNodePadHT + name_rect.height() + mCtx.mNodePadNameAttrs);
  mFirstAttrRect.setWidth(attr_rect.width());
  mFirstAttrRect.setHeight(attr_rect.height());
  update();
}
