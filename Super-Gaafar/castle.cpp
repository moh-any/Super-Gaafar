#include "castle.h"

Castle::Castle(QGraphicsItem *parent)
    : QObject(),QGraphicsPixmapItem(parent)
{
    castle.load(":/images/castle.png");
    setPixmap(castle);
}
