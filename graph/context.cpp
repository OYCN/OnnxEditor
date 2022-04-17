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
  mNodeNormalNamePen.setWidth(1);
  mNodeSelectedNamePen.setWidth(1);
  mNodeNormalAttrsPen.setWidth(1);
  mNodeSelectedAttrsPen.setWidth(1);
  mEdgeNormalPen.setWidth(1);
  mEdgeSelectedPen.setWidth(1);

  mEdgeSelectedPen.setColor(QColor(220, 220, 220));
  mEdgeSelectedPen.setStyle(Qt::DotLine);

  mNodeNormalNameBrush.setStyle(Qt::SolidPattern);
  mNodeSelectedNameBrush.setStyle(Qt::SolidPattern);
  mNodeNormalAttrsBrush.setStyle(Qt::SolidPattern);
  mNodeSelectedAttrsBrush.setStyle(Qt::SolidPattern);
  mEdgeArrowNormalBrush.setStyle(Qt::SolidPattern);
  mEdgeArrowSelectedBrush.setStyle(Qt::SolidPattern);

  mNodeNormalNameBrush.setColor(QColor(255, 255, 255));
  mNodeSelectedNameBrush.setColor(QColor(220, 220, 220));
  mNodeNormalAttrsBrush.setColor(QColor(255, 255, 255));
  mNodeSelectedAttrsBrush.setColor(QColor(220, 220, 220));
  mEdgeArrowSelectedBrush.setColor(QColor(220, 220, 220));

  mNodeNormalNameFont.setFamily("Monospace");
  mNodeSelectedNameFont.setFamily("Monospace");
  mNodeNormalAttrsFont.setFamily("Monospace");
  mNodeSelectedAttrsFont.setFamily("Monospace");
  mEdgeNormalFont.setFamily("Monospace");
  mEdgeSelectedFont.setFamily("Monospace");

  mNodeNormalNameFont.setStyleHint(QFont::TypeWriter);
  mNodeSelectedNameFont.setStyleHint(QFont::TypeWriter);
  mNodeNormalAttrsFont.setStyleHint(QFont::TypeWriter);
  mNodeSelectedAttrsFont.setStyleHint(QFont::TypeWriter);
  mEdgeNormalFont.setStyleHint(QFont::TypeWriter);
  mEdgeSelectedFont.setStyleHint(QFont::TypeWriter);

  mEdgeNormalFont.setPointSize(mNodeNormalNameFont.pointSize() / 1.5);
  mEdgeSelectedFont.setPointSize(mNodeSelectedNameFont.pointSize() / 1.5);

  mEdgeSelectedFont.setBold(true);
}
