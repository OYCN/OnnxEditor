/**
 * @file mainwindow.hpp
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

#ifndef MAINWINDOW_HPP_
#define MAINWINDOW_HPP_

#include <QtWidgets/QMainWindow>

#include "logger.hpp"
#include "graph/graphscene.hpp"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  bool applyByParser();

 private:
  Logger mLogger;
  parser::Parser mParser;
  GraphScene* mScene = nullptr;
};
#endif  // MAINWINDOW_HPP_
