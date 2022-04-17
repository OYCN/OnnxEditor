/**
 * @file graphview.cpp
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

#include "graphview.hpp"

#include <QtCore/QDebug>
#include <QtGui/QWheelEvent>
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QScrollBar>

#include "graph/context.hpp"

GraphView::GraphView(QWidget *parent) : QGraphicsView{parent} {
  setRenderHint(QPainter::Antialiasing, true);
  setMouseTracking(true);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setBackgroundBrush(mCtx.mViewBackgroundColor);
  // this->setBackgroundBrush(QBrush(QPixmap(":/res/grid100_w4_28o.png")));
  setAlignment(Qt::AlignLeft | Qt::AlignTop);

  mScene = new GraphScene(mCtx, this);
  setScene(mScene);
  addMenu();
}

void GraphView::addMenu() {
  mMenu = new QMenu(this);

  mAddNodeAction = new QAction("Add Node", this);
  connect(mAddNodeAction, &QAction::triggered, this, [&]() {
    auto pos = this->mapToScene(this->mapFromGlobal(QCursor::pos()));
    bool isOK;
    QString name = QInputDialog::getText(NULL, "Add Node",
                                         "Please input the new node name",
                                         QLineEdit::Normal, "", &isOK);
    if (isOK) {
      if (name.size() == 0) {
        QMessageBox(QMessageBox::Warning, "Warning", "The name is empty",
                    QMessageBox::Ok, this)
            .exec();
      } else {
        mScene->addNode(pos, name);
      }
    }
  });
  mMenu->addAction(mAddNodeAction);

  mAddEdgeAction = new QAction("Add Edge", this);
  connect(mAddEdgeAction, &QAction::triggered, this, [&]() {
    Q_ASSERT(mSelected.size() == 2);
    GraphNode *from = reinterpret_cast<GraphNode *>(mSelected[0]);
    GraphNode *to = reinterpret_cast<GraphNode *>(mSelected[1]);
    mScene->addEdge(from, to);
    mScene->clearSelection();
  });
  mMenu->addAction(mAddEdgeAction);

  mAddNodeAttrAction = new QAction("Add Node Attr", this);
  connect(mAddNodeAttrAction, &QAction::triggered, this, [&]() {
    Q_ASSERT(mSelected.size() == 1);
    auto pos = this->mapToScene(this->mapFromGlobal(QCursor::pos()));
    bool isOK;
    QString key = QInputDialog::getText(NULL, "Add Key of Node Attr",
                                        "Please input the key of new node attr",
                                        QLineEdit::Normal, "", &isOK);
    if (!isOK || key.size() == 0) {
      QMessageBox(QMessageBox::Warning, "Warning", "The input is empty",
                  QMessageBox::Ok, this)
          .exec();
      return;
    }
    QString value =
        QInputDialog::getText(NULL, "Add Value of Node Attr",
                              "Please input the value of new node attr",
                              QLineEdit::Normal, "", &isOK);
    if (!isOK) {
      QMessageBox(QMessageBox::Warning, "Warning", "Got some error",
                  QMessageBox::Ok, this)
          .exec();
      return;
    }
    GraphNode *node = reinterpret_cast<GraphNode *>(mSelected[0]);
    mScene->setNodeAttr(node, key, value);
  });
  mMenu->addAction(mAddNodeAttrAction);

  connect(mScene, &GraphScene::selectionChanged, this, [&]() {
    auto items = mScene->selectedItems();
    for (const auto &i : items) {
      if (mSelected.count(i) == 0) {
        mSelected.append(i);
      }
    }
#if QT_VERSION < QT_VERSION_CHECK(6, 1, 0)
    for (const auto &i : mSelected) {
      if (items.count(i) == 0) {
        mSelected.removeOne(i);
      }
    }
#else
    mSelected.removeIf([&](QGraphicsItem* i) {
        return items.count(i) == 0;
    });
#endif
  });

  auto layoutAction = new QAction("Layout", this);
  connect(layoutAction, &QAction::triggered, this, [&]() { mScene->layout(); });
  mMenu->addAction(layoutAction);
}

void GraphView::wheelEvent(QWheelEvent *event) {
  if (event->angleDelta().y() > 0) {
    if (mZoom < 2) {
      mZoom *= 1.1;
      this->scale(1.1, 1.1);
    }
  } else {
    if (mZoom > 0.1) {
      mZoom *= 0.9;
      this->scale(0.9, 0.9);
    }
  }
}

void GraphView::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::RightButton) {
    this->mMouseStatus = MouseStatus::kPress;
  } else {
    QGraphicsView::mousePressEvent(event);
  }
}

void GraphView::mouseMoveEvent(QMouseEvent *event) {
  if (mMouseStatus == MouseStatus::kPress) {
    this->viewport()->setCursor(Qt::ClosedHandCursor);
    this->mStartPos = event->pos();
    mMouseStatus = MouseStatus::kDrag;
  }
  if (mMouseStatus == MouseStatus::kDrag) {
    QPoint movPos = event->pos();
    QPoint dis = movPos - mStartPos;
    QScrollBar *hBar = horizontalScrollBar();
    QScrollBar *vBar = verticalScrollBar();
    qreal h = hBar->value() + (isRightToLeft() ? dis.x() : -dis.x());
    qreal v = vBar->value() - dis.y();
    hBar->setValue(h);
    vBar->setValue(v);
    mStartPos = movPos;
  }
  QGraphicsView::mouseMoveEvent(event);
}

void GraphView::mouseReleaseEvent(QMouseEvent *event) {
  if (mMouseStatus == MouseStatus::kDrag) {
    mMouseStatus = MouseStatus::kNone;
    this->viewport()->setCursor(Qt::ArrowCursor);
  } else if (mMouseStatus == MouseStatus::kPress) {
    int nodeNum = 0;
    int edgeNum = 0;
    for (const auto &i : mSelected) {
      auto type = i->data(kItemDataKeyType).toInt();
      if (type == kItemTypeNode) {
        nodeNum++;
      } else if (type == kItemTypeEdge) {
        edgeNum++;
      } else {
        qCritical() << "Unknow value of kItemDataKeyType:" << type;
      }
    }
    //        qDebug() << "Select:" << items.size();
    if (mSelected.size() == 0) {
      mAddNodeAction->setEnabled(true);
    } else {
      mAddNodeAction->setEnabled(false);
    }
    if (nodeNum == 1) {
      mAddNodeAttrAction->setEnabled(true);
    } else {
      mAddNodeAttrAction->setEnabled(false);
    }
    if (nodeNum == 2) {
      mAddEdgeAction->setEnabled(true);
    } else {
      mAddEdgeAction->setEnabled(false);
    }
    mMenu->exec(QCursor::pos());
    mMouseStatus = MouseStatus::kNone;
  }
  QGraphicsView::mouseReleaseEvent(event);
}

void GraphView::keyPressEvent(QKeyEvent *ev) {
  if (ev->key() == Qt::Key_Delete) {
    auto items = mScene->selectedItems();
    for (auto &i : items) {
      auto type = i->data(kItemDataKeyType).toInt();
      if (type == kItemTypeNode) {
        mScene->delNode(reinterpret_cast<GraphNode *>(i));
      } else if (type == kItemTypeEdge) {
        mScene->delEdge(reinterpret_cast<GraphEdge *>(i));
      } else {
        qCritical() << "Unknow value of kItemDataKeyType:" << type;
      }
    }
    return;
  }

  QWidget::keyPressEvent(ev);
}

void GraphView::expand(qreal f) {
  QRectF rectTmp = scene()->sceneRect();
  QPointF ptTopLeft = rectTmp.topLeft();
  QPointF ptBottomRight = rectTmp.bottomRight();
  QPointF ptW_H = f * QPointF(rect().width(), rect().height());
  ptTopLeft -= ptW_H;
  ptBottomRight += ptW_H;
  rectTmp.setTopLeft(ptTopLeft);
  rectTmp.setBottomRight(ptBottomRight);
  scene()->setSceneRect(rectTmp);
  update();
}

void GraphView::center() {
  QScrollBar *hBar = horizontalScrollBar();
  QScrollBar *vBar = verticalScrollBar();
  hBar->setValue(hBar->minimum() + (hBar->maximum() - hBar->minimum()) / 2);
  vBar->setValue(vBar->minimum() + (vBar->maximum() - vBar->minimum()) / 2);
  update();
}
