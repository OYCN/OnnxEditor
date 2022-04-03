#ifndef GRAPHEDGE_H
#define GRAPHEDGE_H

#include <QtWidgets/QGraphicsItem>
#include "context.h"

class GraphNode;

class GraphEdge : public QGraphicsItem
{
public:
    explicit GraphEdge(Context& ctx, GraphNode* from, GraphNode* to, QString name = "");

    void updateAll();

public:
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

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

#endif // GRAPHEDGE_H
