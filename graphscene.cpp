#include "graphscene.h"
#include "graphnode.h"
#include "graphedge.h"
#include <QtGui/QCursor>
#include <QtCore/QDebug>

GraphScene::GraphScene(QObject *parent)
    : QGraphicsScene{parent}
{
    GraphNode* A = new GraphNode(mCtx, "AAAAA");
    A->setPos(0, 0);
    this->addItem(A);
//    GraphNode* B = new GraphNode(mCtx, "BBB");
//    B->setPos(80, 0);
//    this->addItem(B);
    GraphNode* C = new GraphNode(mCtx, "C");
    C->setPos(0, 30);
    this->addItem(C);
//    GraphNode* D = new GraphNode(mCtx, ".");
//    D->setPos(80, 30);
//    this->addItem(D);

//    GraphEdge* AB = new GraphEdge(mCtx, A, B, "A to B");
//    this->addItem(AB);
//    GraphEdge* BC = new GraphEdge(mCtx, B, C, "B to C");
//    this->addItem(BC);
//    GraphEdge* CD = new GraphEdge(mCtx, C, D, "C to D");
//    this->addItem(CD);
//    GraphEdge* DA = new GraphEdge(mCtx, D, A, "D to A");
//    this->addItem(DA);
    GraphEdge* AC = new GraphEdge(mCtx, A, C, "A to C");
    this->addItem(AC);
}

void GraphScene::addNode(QPointF pos, QString name) {
    qDebug() << "add node"  << pos << " Name:" << name;
    GraphNode* node = new GraphNode(mCtx, name);
    node->setPos(pos);
    this->addItem(node);
}

void GraphScene::addEdge(GraphNode* start, GraphNode* stop, QString name) {
    qDebug() << "add edge," << start->getName() << " -> " << stop->getName();
    GraphEdge* edge = new GraphEdge(mCtx, start, stop, name);
    this->addItem(edge);
}
