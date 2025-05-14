#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

class Enemy:public QObject,public QGraphicsPixmapItem {
public:
    Enemy(qreal x);
    virtual void move()=0;

protected:
    qreal velocityX;
    QPixmap spriteSheet;
    QVector<QRect> Rects;
    qreal ground;
    bool facingRight;
    int currentFrame;
    int frameWidth;
    int frameHeight;
    int animationCounter;

private:
    virtual void updateSprite()=0;
    virtual void updateAnimation()=0;
};

#endif // ENEMY_H
