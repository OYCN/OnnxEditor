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
  mNodeNormalPen.setWidth(1);
  mNodeSelectedPen.setWidth(1);
  mEdgeNormalPen.setWidth(1);
  mEdgeSelectedPen.setWidth(1);

  mEdgeSelectedPen.setColor(QColor(220, 220, 220));
  mEdgeSelectedPen.setStyle(Qt::DotLine);

  mNodeNormalBrush.setStyle(Qt::SolidPattern);
  mNodeSelectedBrush.setStyle(Qt::SolidPattern);
  mEdgeArrowNormalBrush.setStyle(Qt::SolidPattern);
  mEdgeArrowSelectedBrush.setStyle(Qt::SolidPattern);

  mNodeNormalBrush.setColor(QColor(255, 255, 255));
  mNodeSelectedBrush.setColor(QColor(220, 220, 220));
  mEdgeArrowSelectedBrush.setColor(QColor(220, 220, 220));

  mNodeNormalFont.setFamily("Monospace");
  mNodeSelectedFont.setFamily("Monospace");
  mEdgeNormalFont.setFamily("Monospace");
  mEdgeSelectedFont.setFamily("Monospace");

  mNodeNormalFont.setStyleHint(QFont::TypeWriter);
  mNodeSelectedFont.setStyleHint(QFont::TypeWriter);
  mEdgeNormalFont.setStyleHint(QFont::TypeWriter);
  mEdgeSelectedFont.setStyleHint(QFont::TypeWriter);

  mEdgeNormalFont.setPointSize(mNodeNormalFont.pointSize() / 1.5);
  mEdgeSelectedFont.setPointSize(mNodeSelectedFont.pointSize() / 1.5);

  mEdgeSelectedFont.setBold(true);
}
