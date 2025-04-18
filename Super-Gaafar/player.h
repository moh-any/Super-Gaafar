#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QTimer>
#include <QRect>
#include <QVector>
#include <QSoundEffect>
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
    bool getIsJumping(){
        return isJumping;
    };
    void setSceneWidth(int w){
        sceneWidth=w;
    }
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
    int sceneWidth=2000;
    QTimer* jumpTimer;

    enum AnimationState {
        IDLE,
        RUNNING,
        JUMPING
    };
    AnimationState currentState;
    int currentFrame;
    int animationSpeed;
    int animationCounter;
    QPixmap spriteSheet;
    QVector<QRect> Rects;
    QSoundEffect* jumpSound;

    void loadSpriteSheet();
    void updateAnimation();
    void updateSprite();
};

#endif // PLAYER_H
