/**
 * @file context.cpp
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

#include "context.hpp"

Context::Context() {
  mEdgeNormalPen.setWidth(1);
  mEdgeSelectedPen.setWidth(1);

  mEdgeSelectedPen.setColor(QColor(220, 220, 220));
  mEdgeSelectedPen.setStyle(Qt::DotLine);

  mEdgeArrowNormalBrush.setStyle(Qt::SolidPattern);
  mEdgeArrowSelectedBrush.setStyle(Qt::SolidPattern);

  mEdgeArrowSelectedBrush.setColor(QColor(220, 220, 220));

  mEdgeNormalFont.setFamily("Monospace");
  mEdgeSelectedFont.setFamily("Monospace");

  mEdgeNormalFont.setStyleHint(QFont::TypeWriter);
  mEdgeSelectedFont.setStyleHint(QFont::TypeWriter);

  mEdgeNormalFont.setPointSize(1.5);
  mEdgeSelectedFont.setPointSize(1.5);

  mEdgeSelectedFont.setBold(true);
}
