#include "coin.h"

Coin::Coin(QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(parent), currentFrame(0)
{
    spriteSheet = QPixmap(":/images/coin.png");
    frameCount = 8;              // number of frames
    frameWidth = spriteSheet.width() / frameCount;
    frameHeight = spriteSheet.height();


    setPixmap(spriteSheet.copy(0, 0, frameWidth, frameHeight));

    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &Coin::nextFrame);
    animationTimer->start(75); // 75 ms per frame


    if (spriteSheet.isNull()) {
        qDebug() << "Failed to load coin image!";
    }
}

void Coin::nextFrame()
{
    currentFrame = (currentFrame + 1) % frameCount;
    int x = currentFrame * frameWidth;
    setPixmap(spriteSheet.copy(x, 0, frameWidth, frameHeight));
}

