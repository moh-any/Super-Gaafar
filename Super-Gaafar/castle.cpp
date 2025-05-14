#include "castle.h"

Castle::Castle(QGraphicsItem *parent)
    : QObject(),QGraphicsPixmapItem(parent)
{
    castle.load(":/images/images/castle.png");
    setPixmap(castle);
}
