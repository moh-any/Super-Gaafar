#include "enemy.h"
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

Enemy::Enemy(qreal x) : QObject(), ground(470), velocityX(0.8), currentFrame(0) {
    facingRight = true;
    setPos(x, ground);
    isSquished=false;
}

void Enemy::squish(){
    isSquished=true;
}

void Enemy::move(){
    QList<QGraphicsItem*> colliding = this->collidingItems(Qt::IntersectsItemBoundingRect);
    bool onGround=false;
    for(auto item:colliding){
        Platform* platform = dynamic_cast<Platform*>(item);
        if(platform){
            if(facingRight) setPos(pos().x()-10, pos().y());
            else setPos(pos().x()+10, pos().y());
            velocityX *= -1;
            facingRight = !facingRight;
        }
        setY(565-pixmap().height());
    }
    if(!isSquished){
        setX(x()+velocityX);
        animationCounter++;
        if(animationCounter >= 3) {
            animationCounter = 0;
            updateAnimation();
        }
    }
    else{
        updateSprite();
    }

}

void Enemy::updateSprite(){
    QRect frameRect(currentFrame, 0, frameWidth, frameHeight);
    QPixmap currentFramePixmap = spriteSheet.copy(frameRect);
    currentFramePixmap = currentFramePixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setPixmap(currentFramePixmap);
    if(facingRight) setPixmap(pixmap().transformed(QTransform().scale(-1,1)));
    if(isSquished) setPixmap(pixmap().transformed(QTransform().scale(1,0.2)));
}

bool Enemy::getIsSquished(){
    return isSquished;
}
