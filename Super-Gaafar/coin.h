#ifndef COIN_H
#define COIN_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Coin : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Coin();

signals:
    void collected();
};

#endif // COIN_H
