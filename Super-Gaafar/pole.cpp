#include "pole.h"

Pole::Pole(QGraphicsItem *parent)
    : QObject(),QGraphicsPixmapItem(parent)
{
    pole.load(":/images/pole.png");
    setPixmap(pole);
}
