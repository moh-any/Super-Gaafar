#include "Goomba.h"
#include "platform.h"
#include <QGraphicsItem>
#include <QTransform>

Goomba::Goomba(qreal x) : Enemy(x) {
    spriteSheet.load(":/images/images/goomba.png");
    frameWidth = 52;
    frameHeight = 50;
    width=52;
    height=50;
    animationCounter = 0;
    currentFrame = 0;
    ground=520;
    facingRight = true;
    setPos(x, ground);
    updateSprite();
}

void Goomba::updateAnimation() {
    currentFrame += 54;
    if(currentFrame >= 862) {
        currentFrame = 0;
    }
    updateSprite();
}

