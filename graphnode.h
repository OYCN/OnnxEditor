#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include <QtWidgets/QGraphicsItem>
#include "context.h"

class GraphNode : public QGraphicsItem
{
public:
    explicit GraphNode(Context& ctx, QString name);


    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;

    QString getName() const {
        return mName;
    }

private:
    Context& mCtx;
    QString mName = "";
};

#endif // GRAPHNODE_H
