#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

class Enemy:public QObject,public QGraphicsPixmapItem {
public:
    Enemy(qreal x);
    void move();

private:

    qreal velocityX;
    QPixmap spriteSheet;
    void loadSpriteSheet();
    QVector<QRect> Rects;
    qreal ground;
    bool facingRight;
    int currentFrame;
    void updateSprite();
    void updateAnimation();
};

#endif // ENEMY_H
