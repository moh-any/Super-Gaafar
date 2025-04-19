#include "flag.h"

Flag::Flag(QGraphicsItem *parent)
    : QObject(),QGraphicsPixmapItem(parent)
{
    flag.load(":/images/mflag.png");
    frameWidth = 115;
    frameHeight = 84;
    setPixmap(flag.copy(0, 0, frameWidth, frameHeight));
    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &Flag::nextFrame);
    animationTimer->start(75);
}

void Flag::nextFrame(){
    currentFrame += 322;
    if (currentFrame >= 5439 ) {
        currentFrame = 0;
    }
    setPixmap(flag.copy(currentFrame, 0, frameWidth, frameHeight));
    if(pos().y()>380){
        setPos(pos().x(),pos().y()-15);
    }
}
