#ifndef CONTEXT_H
#define CONTEXT_H

#include <QtGui/QPainter>

enum ItemDataKey : int{
    kItemDataKeyType = 0
};

enum ItemType : int{
    kItemTypeNode,
    kItemTypeEdge
};

class Context
{
public:
    Context();

public:
    QPen mNodeNormalPen;
    QPen mNodeSelectedPen;
    QPen mEdgeNormalPen;
    QPen mEdgeSelectedPen;

    QBrush mNodeNormalBrush;
    QBrush mNodeSelectedBrush;
    QBrush mEdgeLineNormalBrush;
    QBrush mEdgeLineSelectedBrush;
    QBrush mEdgeArrowNormalBrush;
    QBrush mEdgeArrowSelectedBrush;

    QFont mNodeNormalFont;
    QFont mNodeSelectedFont;
    QFont mEdgeNormalFont;
    QFont mEdgeSelectedFont;

};

#endif // CONTEXT_H
