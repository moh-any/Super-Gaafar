#ifndef PLATFORM_H
#define PLATFORM_H

#include<QGraphicsPixmapItem>

class Platform : public QGraphicsPixmapItem
{
public:
    Platform(qreal x, qreal y, QString s);
};

#endif // PLATFORM_H
