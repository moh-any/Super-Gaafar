#include "enemy.h"
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

Enemy::Enemy(qreal x) : QObject(), ground(470), velocityX(0.8), currentFrame(0) {
    facingRight = true;
    setPos(x, ground);
    // spriteSheet and other members are initialized in derived classes
}


