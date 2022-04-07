/**
 * @file graphscene.cpp
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

#include "graphscene.hpp"

#include <QtCore/QDebug>
#include <QtGui/QCursor>
#include <map>

#include "graphedge.hpp"
#include "graphnode.hpp"

#include "../layout/layout.hpp"

GraphScene::GraphScene(QObject* parent) : QGraphicsScene{parent} {
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
  qDebug() << "add node" << pos << " Name:" << name;
  GraphNode* node = new GraphNode(mCtx, name);
  node->setPos(pos);
  this->addItem(node);
  mNodes.push_back(node);
}

void GraphScene::addEdge(GraphNode* start, GraphNode* stop, QString name) {
  qDebug() << "add edge," << start->getName() << " -> " << stop->getName();
  GraphEdge* edge = new GraphEdge(mCtx, start, stop, name);
  this->addItem(edge);
  mEdges.push_back(edge);
}

void GraphScene::layout() {
  qDebug() << "Layout";
  auto le = layout::getLayoutEngine(layout::kOGDF);
  std::map<GraphNode*, layout::Node_t*> node_map;
  std::vector<layout::Node_t*> nodes;
  for (const auto& node : mNodes) {
    auto rect = node->boundingRect();
    auto n = le->addNode(rect.width(), rect.height());
    n->mData["item"] = node;
    node_map[node] = n;
    nodes.push_back(n);
  }
  for (const auto& edge : mEdges) {
    auto node1 = edge->getFrom();
    auto node2 = edge->getTo();
    auto n1 = node_map[node1];
    auto n2 = node_map[node2];
    auto e = le->addEdge(n1, n2);
  }
  le->layout();
  for (const auto& n : nodes) {
    auto node = std::any_cast<GraphNode*>(n->mData.at("item"));
    node->setPos(n->mX, n->mY);
  }
}
