#ifndef PLATFORM_H
#define PLATFORM_H

#include<QGraphicsPixmapItem>

class Platform : public QGraphicsPixmapItem
{
public:
    Platform(qreal x, qreal y, QString s, int length=1);
};

#endif // PLATFORM_H
