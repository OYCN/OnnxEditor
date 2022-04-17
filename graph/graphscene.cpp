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

#include "../layout/layout.hpp"
#include "graphedge.hpp"
#include "graphnode.hpp"

GraphScene::GraphScene(QObject* parent) : QGraphicsScene{parent} {}

GraphNode* GraphScene::addNode(QString name) {
  qDebug() << "add node" << name;
  GraphNode* node = new GraphNode(mCtx, name);
  Q_ASSERT(mNode2Edges.count(node) == 0);
  this->addItem(node);
  mNodes.append(node);
  mNode2Edges[node] = QList<GraphEdge*>();
  return node;
}

GraphNode* GraphScene::addNode(QPointF pos, QString name) {
  auto node = addNode(name);
  node->setPos(pos);
  return node;
}

GraphEdge* GraphScene::addEdge(GraphNode* start, GraphNode* stop,
                               QString name) {
  Q_ASSERT(mNode2Edges.count(start) == 1);
  Q_ASSERT(mNode2Edges.count(stop) == 1);
  qDebug() << "add edge," << start->getName() << " -> " << stop->getName();
  GraphEdge* edge = new GraphEdge(mCtx, start, stop, name);
  Q_ASSERT(mNode2Edges[start].count(edge) == 0);
  Q_ASSERT(mNode2Edges[stop].count(edge) == 0);
  mNode2Edges[start].append(edge);
  mNode2Edges[stop].append(edge);
  this->addItem(edge);
  mEdges.append(edge);
  return edge;
}

void GraphScene::delNode(GraphNode* node) {
  Q_ASSERT(mNodes.count(node) == 1);
  mNodes.removeOne(node);
  Q_ASSERT(mNode2Edges.count(node) == 1);
  for (const auto& e : mNode2Edges[node]) {
    if (node == e->getFrom()) e->setFrom(nullptr);
    if (node == e->getTo()) e->setTo(nullptr);
  }
  mNode2Edges.remove(node);
  removeItem(node);
}

void GraphScene::delEdge(GraphEdge* edge) {
  auto start = edge->getFrom();
  auto stop = edge->getTo();
  Q_ASSERT(mNode2Edges.count(start) == 1);
  Q_ASSERT(mNode2Edges.count(stop) == 1);
  Q_ASSERT(mNode2Edges[start].count(edge) == 1);
  Q_ASSERT(mNode2Edges[stop].count(edge) == 1);
  mNode2Edges[start].removeOne(edge);
  mNode2Edges[stop].removeOne(edge);
  Q_ASSERT(mEdges.count(edge) == 0);
  mEdges.removeOne(edge);
  removeItem(edge);
}

void GraphScene::setNodeAttr(GraphNode* node, QString key, QString value) {
  qDebug() << "add node attr," << node->getName() << ": " << key << "=" << value;
  node->setAttr(key, value);
  node->updateAll();
  Q_ASSERT(mNode2Edges.count(node) == 1);
  for (auto& e : mNode2Edges[node]) {
    e->updateAll();
  }
}

void GraphScene::layout() {
  auto le = layout::getLayoutEngine(layout::kOGDF);
  // auto le = layout::getLayoutEngine(layout::kNone);
  std::map<GraphNode*, layout::Node_t*> node_map;
  std::vector<layout::Node_t*> nodes;
  for (const auto& node : mNodes) {
    auto rect = node->boundingRect();
    // qDebug() << node->getName() << rect;
    auto n = le->addNode(rect.width(), rect.height());
    Q_ASSERT(node_map.count(node) == 0);
    node_map.insert(std::make_pair(node, n));
    nodes.push_back(n);
  }
  for (const auto& edge : mEdges) {
    auto node1 = edge->getFrom();
    auto node2 = edge->getTo();
    auto n1 = node_map.at(node1);
    auto n2 = node_map.at(node2);
    le->addEdge(n1, n2);
  }
  le->layout();
  for (const auto& item : node_map) {
    auto node = item.first;
    auto n = item.second;
    // qDebug() << node->getName() << "x:" << n->mX << "y" << n->mY;
    node->setPos(n->mX, n->mY);
  }
  for (const auto& item : mEdges) {
    item->updateAll();
  }
  update();
}
