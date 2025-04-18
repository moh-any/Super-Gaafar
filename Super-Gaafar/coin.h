#ifndef COIN_H
#define COIN_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QObject>

class Coin : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Coin(QGraphicsItem *parent = nullptr);

private slots:
    void nextFrame();

private:
    QPixmap spriteSheet;
    int currentFrame;
    int frameCount;
    int frameWidth;
    int frameHeight;
    QTimer *animationTimer;
    double ground;
};

#endif // COIN_H
