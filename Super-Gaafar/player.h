#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QTimer>

class Player:public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Player(QGraphicsItem *parent = nullptr);
    void moveLeft();
    void moveRight();
    void stopMoving();
    void jump();
    void update();
    void applyGravity();

private:
    QPixmap sprite;
    bool facingRight;
    double velocityX;
    double movementSpeed;
    double velocityY;
    double gravity;
    bool isJumping;
    double jumpForce;
    double ground;
    QTimer* jumpTimer;

signals:
void collidedWithCoin();

};

#endif // PLAYER_H
