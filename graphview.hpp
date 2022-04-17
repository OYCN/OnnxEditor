/**
 * @file graphview.hpp
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

#ifndef GRAPHVIEW_HPP_
#define GRAPHVIEW_HPP_

#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QMenu>

#include "graph/graphscene.hpp"

enum class MouseStatus { kNone, kPress, kDrag };

class GraphView : public QGraphicsView {
  Q_OBJECT

 public:
  explicit GraphView(QWidget* parent = nullptr);

 public:
  void expand(qreal f);
  void center();
  GraphScene* getScene() const { return mScene; }

 private:
  void addMenu();

 protected:
  void wheelEvent(QWheelEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void keyPressEvent(QKeyEvent* ev) override;

 private:
  MouseStatus mMouseStatus = MouseStatus::kNone;
  QPoint mStartPos;
  qreal mZoom = 1;

  GraphScene* mScene = nullptr;
  QAction* mAddNodeAction = nullptr;
  QAction* mAddNodeAttrAction = nullptr;
  QAction* mAddEdgeAction = nullptr;
  QMenu* mMenu = nullptr;
  QList<QGraphicsItem*> mSelected;
};

#endif  // GRAPHVIEW_HPP_
