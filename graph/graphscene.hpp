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

#include "context.hpp"

class GraphNode;

class GraphScene : public QGraphicsScene {
  Q_OBJECT
 public:
  explicit GraphScene(QObject* parent = nullptr);

  void addNode(QPointF pos, QString name);
  void addEdge(GraphNode* start, GraphNode* stop, QString name);

 private:
  Context mCtx;
};

#endif  // GRAPH_GRAPHSCENE_HPP_
