// coin.cpp
#include "coin.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsItem>

Coin::Coin() {
    setPixmap(QPixmap(":/images/coin.png").scaled(32, 32));
}
