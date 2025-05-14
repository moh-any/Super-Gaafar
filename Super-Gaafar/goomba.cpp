#include "Goomba.h"
#include "platform.h"
#include <QGraphicsItem>
#include <QTransform>

Goomba::Goomba(qreal x) : Enemy(x) {
    spriteSheet.load(":/images/images/goomba.png");
    frameWidth = 52;
    frameHeight = 50;
    animationCounter = 0;
    currentFrame = 0;
    ground=520;
    facingRight = true;
    setPos(x, ground);
    updateSprite();
}

void Goomba::move() {
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

void Goomba::updateAnimation() {
    currentFrame += 54;
    if(currentFrame >= 862) {
        currentFrame = 0;
    }
    updateSprite();
}

void Goomba::updateSprite() {
    QRect frameRect(currentFrame, 0, frameWidth, frameHeight);
    QPixmap currentFramePixmap = spriteSheet.copy(frameRect);
    setPixmap(currentFramePixmap);
    if(facingRight) setPixmap(pixmap().transformed(QTransform().scale(-1,1)));
}

