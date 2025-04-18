#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>

class Enemy:public QObject,public QGraphicsPixmapItem {
public:
    Enemy(qreal x);
    void move();
    void updateSprite();
private:
    qreal velocityX;
    QPixmap spriteSheet;
    void loadSpriteSheet();
    QVector<QRect> Rects;
    qreal ground;
    bool facingRight;
};

#endif // ENEMY_H
