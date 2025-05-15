#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <platform.h>
#include <ground.h>
class Enemy:public QObject,public QGraphicsPixmapItem {
public:
    Enemy(qreal x);
    virtual void move();
    void squish();
    bool getIsSquished();
    virtual void updateSprite();
    virtual void updateAnimation()=0;

protected:
    qreal velocityX;
    QPixmap spriteSheet;
    QVector<QRect> Rects;
    qreal ground;
    bool facingRight;
    bool isSquished;
    int currentFrame;
    int frameWidth;
    int frameHeight;
    int animationCounter;
    int width;
    int height;
};

#endif // ENEMY_H
