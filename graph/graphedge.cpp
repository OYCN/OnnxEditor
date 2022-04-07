/**
 * @file graphedge.cpp
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

#include "graphedge.hpp"

#include <QtCore/QDebug>
#include <QtGui/QPainter>

#include "graphnode.hpp"

GraphEdge::GraphEdge(Context& ctx, GraphNode* from, GraphNode* to, QString name)
    : mCtx(ctx), mName(name), mFrom(from), mTo(to) {
  setData(kItemDataKeyType, kItemTypeEdge);
  setFlag(QGraphicsItem::ItemIsSelectable, true);
  updateAll();
}

QRectF GraphEdge::boundingRect() const {
  return mPath.boundingRect() | mNameRect | mArrow.boundingRect();
}

QPainterPath GraphEdge::shape() const {
  QPainterPathStroker ps;
  QPen* pen;

  if (isSelected()) {
    pen = &mCtx.mEdgeSelectedPen;
  } else {
    pen = &mCtx.mEdgeNormalPen;
  }

  ps.setCapStyle(pen->capStyle());
  ps.setWidth(pen->widthF() + 10);
  ps.setJoinStyle(pen->joinStyle());
  ps.setMiterLimit(pen->miterLimit());

  QPainterPath p = ps.createStroke(mPath);
  p.addRect(mNameRect);
  p.addPolygon(mArrow);
  return p;
}

void GraphEdge::paint(QPainter* painter, const QStyleOptionGraphicsItem*,
                      QWidget*) {
  painter->save();

  if (isSelected()) {
    painter->setPen(mCtx.mEdgeSelectedPen);
    painter->setBrush(mCtx.mEdgeLineSelectedBrush);
    painter->setFont(mCtx.mEdgeSelectedFont);
  } else {
    painter->setPen(mCtx.mEdgeNormalPen);
    painter->setBrush(mCtx.mEdgeLineNormalBrush);
    painter->setFont(mCtx.mEdgeNormalFont);
  }

  painter->drawPath(mPath);
  //    painter->drawText(mText, mName);
  painter->drawText(mNameRect, Qt::AlignCenter, mName);
  if (isSelected()) {
    painter->setBrush(mCtx.mEdgeArrowSelectedBrush);
  } else {
    painter->setBrush(mCtx.mEdgeArrowNormalBrush);
  }
  painter->drawPolygon(mArrow);

  painter->restore();
}

#if QT_VERSION < QT_VERSION_CHECK(5, 14, 0)
inline bool intersection(const QLineF& l1, const QLineF& l2) {
  if ((l1.x1() > l1.x2() ? l1.x1() : l1.x2()) <
          (l2.x1() < l2.x2() ? l2.x1() : l2.x2()) ||
      (l1.y1() > l1.y2() ? l1.y1() : l1.y2()) <
          (l2.y1() < l2.y2() ? l2.y1() : l2.y2()) ||
      (l2.x1() > l2.x2() ? l2.x1() : l2.x2()) <
          (l1.x1() < l1.x2() ? l1.x1() : l1.x2()) ||
      (l2.y1() > l2.y2() ? l2.y1() : l2.y2()) <
          (l1.y1() < l1.y2() ? l1.y1() : l1.y2())) {
    return false;
  }
  if ((((l1.x1() - l2.x1()) * (l2.y2() - l2.y1()) -
        (l1.y1() - l2.y1()) * (l2.x2() - l2.x1())) *
       ((l1.x2() - l2.x1()) * (l2.y2() - l2.y1()) -
        (l1.y2() - l2.y1()) * (l2.x2() - l2.x1()))) > 0 ||
      (((l2.x1() - l1.x1()) * (l1.y2() - l1.y1()) -
        (l2.y1() - l1.y1()) * (l1.x2() - l1.x1())) *
       ((l2.x2() - l1.x1()) * (l1.y2() - l1.y1()) -
        (l2.y2() - l1.y1()) * (l1.x2() - l1.x1()))) > 0) {
    return false;
  }
  return true;
}
#endif

void GraphEdge::updateAll() {
  // update start & stop pos
  QPointF fromPos = mFrom->pos();
  QRectF fromRect = mFrom->boundingRect();
  fromRect.translate(fromPos);
  QPointF toPos = mTo->pos();
  QRectF toRect = mTo->boundingRect();
  toRect.translate(toPos);

  QPointF fc = QPointF(fromRect.x() + fromRect.width() / 2,
                       fromRect.y() + fromRect.height() / 2);
  QPointF tc = QPointF(toRect.x() + toRect.width() / 2,
                       toRect.y() + toRect.height() / 2);

  QLineF vec(fc, tc);

  auto func = [&vec](const QRectF& rect, const QPointF& c, QPointF& point) {
    QPolygonF r(rect);
    for (int i = 1; i < r.count(); i++) {
      QLineF fl(r.at(i - 1), r.at(i));
#if QT_VERSION < QT_VERSION_CHECK(5, 14, 0)
      if (intersection(fl, vec)) {
#else
      if (fl.intersects(vec) == QLineF::BoundedIntersection) {
#endif
        switch (i) {
          case 1:
            // TOP
            point = QPointF(c.x(), rect.y());
            return;
          case 2:
            // RIGHT
            point = QPointF(rect.x() + rect.width(), c.y());
            return;
          case 3:
            // BOTTOM
            point = QPointF(c.x(), rect.y() + rect.height());
            return;
          case 4:
            // LEFT
            point = QPointF(rect.x(), c.y());
            return;
          default:
            qCritical() << "err for:" << i;
            return;
        }
      }
    }
  };  // NOLINT(readability/braces)

  func(fromRect, fc, mStart);
  func(toRect, tc, mStop);

// update path
#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
  {  // QT5
    auto t = QPainterPath();
    mPath.swap(t);
  }
#else
  mPath.clear();
#endif
  mPath.moveTo(mStart);
  // QPointF c1 = QPointF((mStart.x() + mStop.x()) / 2, mStart.y());
  // QPointF c2 = QPointF((mStart.x() + mStop.x()) / 2, mStop.y());
  // mPath.cubicTo(c1, c2, mStop);
  //    mPath.lineTo(mStop);
  QPointF c0 = QPointF((mStart.x() + mStop.x()) / 2, mStart.y());
  mPath.quadTo(c0, mStop);

  // update text pos
  QLineF l(mStart, mStop);
  mText = l.center();
  QFont* font;
  if (isSelected()) {
    font = &mCtx.mEdgeSelectedFont;
  } else {
    font = &mCtx.mEdgeNormalFont;
  }

  QFontMetrics fm(*font);
  QRectF rect = fm.boundingRect(mName);
  mNameRect = QRectF(mText.x(), mText.y(), rect.width(), rect.height());

  // update arrow
  mArrow.clear();
  QLineF t = QLineF(mStop, mStart);
  t.setLength(3);
  QLineF p = QLineF(t.p2(), t.p1()).normalVector();
  QPointF dp = p.p2() - p.p1();
  mArrow.append(mStop);
  mArrow.append(p.p1() + dp);
  mArrow.append(p.p1() - dp);
}
