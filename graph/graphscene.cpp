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
  this->addItem(node);
  mNodes.push_back(node);
  return node;
}

GraphNode* GraphScene::addNode(QPointF pos, QString name) {
  auto node = addNode(name);
  node->setPos(pos);
  return node;
}

GraphEdge* GraphScene::addEdge(GraphNode* start, GraphNode* stop,
                               QString name) {
  qDebug() << "add edge," << start->getName() << " -> " << stop->getName();
  GraphEdge* edge = new GraphEdge(mCtx, start, stop, name);
  this->addItem(edge);
  mEdges.push_back(edge);
  return edge;
}

void GraphScene::setNodeAttr(GraphNode* node, QString key, QString value) {
  qDebug() << "add node attr," << node->getName() << ": " << key << "=" << value;
  node->setAttr(key, value);
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
