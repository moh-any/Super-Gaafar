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
    width=96;
    height=96;
    facingRight = true;
    setPos(x, ground);
    updateSprite();
}

void RedT::updateAnimation() {
    currentFrame += 179;
    if(currentFrame >= 3521) {
        currentFrame = 0;
    }
    updateSprite();
}


