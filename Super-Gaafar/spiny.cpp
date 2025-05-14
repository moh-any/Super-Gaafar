#include "spiny.h"
#include "platform.h"
#include <QGraphicsItem>
#include <QTransform>

Spiny::Spiny(qreal x) : Enemy(x) {
    spriteSheet.load(":/images/images/spiny.png");
    frameWidth = 120;
    frameHeight = 93;
    animationCounter = 0;
    currentFrame = 0;
    ground=480;
    facingRight = true;
    setPos(x, ground);
    updateSprite();
}

void Spiny::move() {
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

void Spiny::updateAnimation() {
    currentFrame += 238;
    if(currentFrame >= 3569) {
        currentFrame = 0;
    }
    updateSprite();
}

void Spiny::updateSprite() {
    QRect frameRect(currentFrame, 0, frameWidth, frameHeight);
    QPixmap currentFramePixmap = spriteSheet.copy(frameRect);
    setPixmap(currentFramePixmap);
    if(facingRight) setPixmap(pixmap().transformed(QTransform().scale(-1,1)));
}

