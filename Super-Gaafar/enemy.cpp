#include "enemy.h"
#include "platform.h"
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

Enemy::Enemy(qreal x):QObject(), ground(505), velocityX(1) {
    facingRight = true;
    setPos(x, ground);
    loadSpriteSheet();
    updateSprite();
}

void Enemy::loadSpriteSheet(){
    spriteSheet.load(":/images/mario.png");
    int frameWidth=57;
    int frameHeight=75;
    int runningFrameCount=21;
    for(int i=0;i<runningFrameCount; i++){
        Rects.append(QRect(i*frameWidth,0,frameWidth,frameHeight));
    }
}

void Enemy::move(){
    QList<QGraphicsItem*> colliding = this->collidingItems(Qt::IntersectsItemBoundingRect);
    for(auto item:colliding){
        Platform* platform = dynamic_cast<Platform*>(item);
        if (platform){
            velocityX *= -1;
            facingRight = !facingRight;
        }
    }

    setX(x()+velocityX);
}

void Enemy::updateSprite(){
    QRect frameRect;
    QPixmap currentFramePixmap=spriteSheet.copy(frameRect);
    currentFramePixmap=currentFramePixmap.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    if(facingRight){
        currentFramePixmap=currentFramePixmap.transformed(QTransform().scale(-1, 1));
    }
    setPixmap(currentFramePixmap);
}
