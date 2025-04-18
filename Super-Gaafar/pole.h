#ifndef POLE_H
#define POLE_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Pole : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Pole(QGraphicsItem *parent = nullptr);
private:
    QPixmap pole;
};

#endif // POLE_H
