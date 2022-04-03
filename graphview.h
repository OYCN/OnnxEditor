#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QtWidgets/QGraphicsView>
#include "graph/graphscene.h"
#include <QtWidgets/QMenu>

enum class MouseStatus {
    kNone,
    kPress,
    kDrag
};

class GraphView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphView(QWidget *parent = nullptr);

public:
    void expand(qreal f);
    void center();

protected:
    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent *ev) override;

private:
    MouseStatus mMouseStatus = MouseStatus::kNone;
    QPoint mStartPos;
    qreal mZoom = 1;

    GraphScene* mScene = nullptr;
    QAction* mAddNodeAction = nullptr;
    QAction* mAddEdgeAction = nullptr;
    QMenu* mMenu = nullptr;
    QList<QGraphicsItem*> mSelected;
};

#endif // GRAPHVIEW_H
