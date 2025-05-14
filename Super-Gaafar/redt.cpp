#include "redt.h"
#include "platform.h"
#include <QGraphicsItem>
#include <QTransform>

RedT::RedT(qreal x) : Enemy(x) {
    spriteSheet.load(":/images/images/redt.png");
    frameWidth = 130;
    frameHeight = 140;
    animationCounter = 0;
    currentFrame = 0;
    facingRight = true;
    setPos(x, ground);
    updateSprite();
}

void RedT::move() {
    QList<QGraphicsItem*> colliding = this->collidingItems(Qt::IntersectsItemBoundingRect);
    for(auto item : colliding) {
        Platform* platform = dynamic_cast<Platform*>(item);
        if(platform) {
            if(facingRight) setPos(pos().x()-10, pos().y());
            else setPos(pos().x()+10, pos().y());
            velocityX *= -1;
            facingRight = !facingRight;
        }
    }
    setX(x() + velocityX);
    animationCounter++;
    if(animationCounter >= 3) {
        animationCounter = 0;
        updateAnimation();
    }
}

void RedT::updateAnimation() {
    currentFrame += 179;
    if(currentFrame >= 3521) {
        currentFrame = 0;
    }
    updateSprite();
}

void RedT::updateSprite() {
    QRect frameRect(currentFrame, 0, frameWidth, frameHeight);
    QPixmap currentFramePixmap = spriteSheet.copy(frameRect);
    currentFramePixmap = currentFramePixmap.scaled(96, 96, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setPixmap(currentFramePixmap);
    if(facingRight) setPixmap(pixmap().transformed(QTransform().scale(-1,1)));
}

