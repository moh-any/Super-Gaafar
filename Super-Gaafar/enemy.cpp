#include "enemy.h"
#include "platform.h"
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

Enemy::Enemy(qreal x):QObject(), ground(470), velocityX(1),currentFrame(0){
    facingRight = true;
    setPos(x, ground);
    loadSpriteSheet();
    updateAnimation();
}

void Enemy::loadSpriteSheet(){
    spriteSheet.load(":/images/redt.png");
    double frameWidth=59.5;
    int frameHeight=75;
    int runningFrameCount=20;
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
    updateAnimation();
}

void Enemy::updateAnimation(){
    currentFrame=(currentFrame+1)%Rects.size();
    QRect frameRect=Rects[currentFrame];
    QPixmap currentFramePixmap=spriteSheet.copy(frameRect);
    currentFramePixmap=currentFramePixmap.scaled(128, 128, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    if(facingRight){
        currentFramePixmap=currentFramePixmap.transformed(QTransform().scale(-1, 1));
    }
    setPixmap(currentFramePixmap);
}

