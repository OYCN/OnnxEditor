#ifndef GRAPHSCENE_H
#define GRAPHSCENE_H

#include <QtWidgets/QGraphicsScene>
#include "context.h"

class GraphNode;

class GraphScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphScene(QObject *parent = nullptr);

    void addNode(QPointF pos, QString name);
    void addEdge(GraphNode* start, GraphNode* stop, QString name);

private:
    Context mCtx;
};

#endif // GRAPHSCENE_H
