#include "player.h"
#include "platform.h"
#include <QGraphicsScene>
#include <QRectF>
#include <QTransform>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QTimer>
#include <ground.h>
#include <QObject>

Player::Player(QGraphicsItem *parent):QObject() ,QGraphicsPixmapItem(parent),facingRight(true),velocityX(0),movementSpeed(5.0),velocityY(0),gravity(0.5),isJumping(false),jumpForce(15.0),ground(505),currentState(IDLE),currentFrame(0),animationSpeed(5),animationCounter(0){
    setPos(0,ground);
    loadSpriteSheet();
    updateSprite();
    jumpSound=new QSoundEffect(this);
    jumpSound->setSource(QUrl("qrc:/sounds/jump.wav"));
    jumpSound->setVolume(0.25);
}


void Player::moveLeft(){
    velocityX=-movementSpeed;
    currentState=RUNNING;
    QList<QGraphicsItem *> colliding = collidingItems();
    for (auto item : colliding){
        Platform *platform = dynamic_cast<Platform *> (item);
        if (!facingRight && platform){
            stopMoving();
        }
    }
    if(facingRight){
        QPixmap flippedSprite=sprite.transformed(QTransform().scale(-1, 1));
        setPixmap(flippedSprite);
        facingRight=false;
    }
}

void Player::moveRight(){
    velocityX=movementSpeed;
    currentState=RUNNING;
    QList<QGraphicsItem *> colliding = collidingItems();
    for (auto item : colliding){
        Platform *platform = dynamic_cast<Platform *> (item);
        if (facingRight && platform){
            stopMoving();
        }
    }
    if(!facingRight) {
        setPixmap(sprite);
        facingRight=true;
    }
}

void Player::stopMoving(){
    velocityX=0;
    currentState=IDLE;
}

void Player::jump(){
    if(!isJumping){
        isJumping=true;
        velocityY=-jumpForce;
        jumpSound->play();
        currentState=JUMPING;
        // qDebug() << "Jumped";
    }
}

void Player::update(){
    if(pos().x()<=0){
        setPos(0,pos().y());
    }
    else if(pos().x()+boundingRect().width()>=sceneWidth){
        setPos(sceneWidth-boundingRect().width(),pos().y());
    }
    setPos(pos().x()+velocityX,pos().y());
    updateAnimation();
    applyGravity();
}

void Player::applyGravity(){
    velocityY+=gravity;
    setPos(pos().x(),pos().y()+velocityY);
    QList<QGraphicsItem*> colliding = this->collidingItems(Qt::IntersectsItemBoundingRect);
    for(auto item:colliding){
        qDebug() << " collided with:" << typeid(*item).name();
        Ground* tmp1=dynamic_cast<Ground*>(item);
        Platform* tmp2=dynamic_cast<Platform*>(item);

        if(tmp1){
            setPos(pos().x(),ground+1);
            velocityY=0;
            isJumping=false;
            if(velocityX!=0){
                currentState=RUNNING;
            }
            else{
                currentState=IDLE;
            }
        }
        else if (tmp2){
            if (velocityY > 0){
                setY(item->y() - pixmap().height());
                velocityY=0;
                isJumping=false;
                if (velocityX!=0){
                    currentState=RUNNING;
                }
                else{
                    currentState=IDLE;
                }
            }
            else{
                setY(tmp2->y() + tmp2->pixmap().height()+1);
                velocityY=5;
            }
        }
    }
}

void Player::loadSpriteSheet(){
    spriteSheet.load(":/images/mario.png");
    int frameWidth=57;
    int frameHeight=75;
    int runningFrameCount=21;
    for(int i=0;i<runningFrameCount; i++){
        Rects.append(QRect(i*frameWidth,0,frameWidth,frameHeight));
    }
}

void Player::updateAnimation(){
    switch(currentState){
    case IDLE:
        currentFrame=0;
        break;
    case RUNNING:
        currentFrame=(currentFrame+1)%Rects.size();
        break;
    case JUMPING:
        currentFrame=0;
        break;
    }
    updateSprite();
}

void Player::updateSprite(){
    QRect frameRect;
    switch(currentState){
    case IDLE:
        frameRect=Rects[currentFrame];
        break;
    case RUNNING:
        frameRect=Rects[currentFrame];
        break;
    case JUMPING:
        frameRect=Rects[currentFrame];
        break;
    }
    QPixmap currentFramePixmap=spriteSheet.copy(frameRect);
    currentFramePixmap=currentFramePixmap.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    if(!facingRight){
        currentFramePixmap=currentFramePixmap.transformed(QTransform().scale(-1, 1));
    }
    setPixmap(currentFramePixmap);
}
