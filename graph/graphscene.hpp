/**
 * @file graphscene.hpp
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

#ifndef GRAPH_GRAPHSCENE_HPP_
#define GRAPH_GRAPHSCENE_HPP_

#include <QtWidgets/QGraphicsScene>
#include <QtCore/QMap>

#include "context.hpp"

class GraphNode;
class GraphEdge;

class GraphScene : public QGraphicsScene {
  Q_OBJECT
 public:
  explicit GraphScene(QObject* parent = nullptr);

  GraphNode* addNode(QString name);
  GraphNode* addNode(QPointF pos, QString name);
  GraphEdge* addEdge(GraphNode* start, GraphNode* stop, QString name = "");
  void delNode(GraphNode* node);
  void delEdge(GraphEdge* edge);

  void setNodeAttr(GraphNode* node, QString key, QString value);

  void layout();

 private:
  Context mCtx;
  QList<GraphNode*> mNodes;
  QList<GraphEdge*> mEdges;
  QMap<GraphNode*, QList<GraphEdge*>> mNode2Edges;
};

#endif  // GRAPH_GRAPHSCENE_HPP_
