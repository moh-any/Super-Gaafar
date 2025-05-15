#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QTimer>
#include <QRect>
#include <QVector>
#include <QSoundEffect>
#include <QPainter>
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
    bool getFacingRight(){
        return facingRight;
    }
    void setMovementSpeed(double speed);
    void setJumpForce(double force);
    void applyGiantPowerUp();
    void setVelocityX(double vx) { velocityX = vx; }
    void setVelocityY(double vy) { velocityY = vy; }
    double getVelocityX() { return velocityX; }
    double getVelocityY() { return velocityY; }
    void setOnGround(bool val) { isJumping = !val; }
    bool isOnGround() { return !isJumping; }
    int getLives(){
        return lives;
    }
    void loseLife();
    bool isInvincible(){
        return invincible;
    }
    void setSpeedMultiplier(double multiplier);
    void setJumpBoost(double boost);
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
    int height=96;
    int width=96;
    QTimer* jumpTimer;
    int counter;

    enum AnimationState {
        IDLE,
        RUNNING,
        JUMPING
    };
    AnimationState currentState;
    int currentFrame;
    QPixmap spriteSheet;
    QVector<QRect> Rects;
    QSoundEffect* jumpSound;

    void loadSpriteSheet();
    void updateAnimation();
    void updateSprite();
    // --- Lives and Invincibility ---
    int lives = 3;
    bool invincible = false;
    QTimer* invincibleTimer = nullptr;
    QTimer* flickerTimer = nullptr;
    bool flickerVisible = true;
};

#endif // PLAYER_H
