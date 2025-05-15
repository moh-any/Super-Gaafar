#include "spiny.h"
#include "platform.h"
#include <QGraphicsItem>
#include <QTransform>

Spiny::Spiny(qreal x) : Enemy(x) {
    spriteSheet.load(":/images/images/spiny.png");
    frameWidth = 120;
    frameHeight = 93;
    width=120;
    height=93;
    animationCounter = 0;
    currentFrame = 0;
    ground=480;
    facingRight = true;
    setPos(x, ground);
    updateSprite();
}


void Spiny::updateAnimation() {
    currentFrame += 238;
    if(currentFrame >= 3569) {
        currentFrame = 0;
    }
    updateSprite();
}

