#include "player.h"
#include <QGraphicsScene>
#include <QRectF>
#include <QTransform>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QTimer>
#include <QObject>
Player::Player(QGraphicsItem *parent):QGraphicsPixmapItem(parent),facingRight(true),velocityX(0),movementSpeed(5.0),velocityY(0),gravity(0.5),isJumping(false),jumpForce(15.0),ground(600),currentState(IDLE),currentFrame(0),animationSpeed(5),animationCounter(0){
    setPos(800,ground);
    loadSpriteSheet();
    updateSprite();
}


void Player::moveLeft(){
    velocityX=-movementSpeed;
    if(facingRight){
        QPixmap flippedSprite=sprite.transformed(QTransform().scale(-1, 1));
        setPixmap(flippedSprite);
        facingRight=false;
    }
    currentState=RUNNING;
}

void Player::moveRight(){
    velocityX=movementSpeed;
    if(!facingRight) {
        setPixmap(sprite);
        facingRight=true;
    }
    currentState=RUNNING;
}

void Player::stopMoving(){
    velocityX=0;
    currentState=IDLE;
}

void Player::jump(){
    if(!isJumping){
        isJumping=true;
        velocityY=-jumpForce;
        currentState=JUMPING;
    }
}

void Player::update(){
    setPos(pos().x()+velocityX,pos().y());
    if(pos().x()<0){
        setPos(0,pos().y());
    }
    else if(pos().x()+boundingRect().width()>800){
        setPos(800-boundingRect().width(), pos().y());
    }
    updateAnimation();
    applyGravity();
}

void Player::applyGravity(){
    velocityY+=gravity;
    setPos(pos().x(),pos().y()+velocityY);
    if(pos().y()>=ground){
        setPos(pos().x(),ground);
        velocityY=0;
        isJumping=false;
        if(velocityX!=0){
            currentState=RUNNING;
        }
        else{
            currentState=IDLE;
        }
    }
}

void Player::loadSpriteSheet(){
    spriteSheet.load(":/images/mario.png");
    idleRects.append(QRect(110,0,50,75));
    int frameWidth=50;
    int frameHeight=75;
    int runningFrameCount=21;
    for(int i=0;i<runningFrameCount; i++){
        runRects.append(QRect(i*frameWidth+7*i,0,frameWidth,frameHeight));
    }
    jumpRects.append(QRect(0,0,50,75));
}

void Player::updateAnimation(){
    switch(currentState){
    case IDLE:
        currentFrame=(currentFrame+1)%idleRects.size();
        break;
    case RUNNING:
        currentFrame=(currentFrame+1)%runRects.size();
        break;
    case JUMPING:
        currentFrame=(currentFrame+1)%jumpRects.size();
        break;
    }
    updateSprite();
}

void Player::updateSprite(){
    QRect frameRect;
    switch(currentState){
    case IDLE:
        frameRect=idleRects[currentFrame];
        break;
    case RUNNING:
        frameRect=runRects[currentFrame];
        break;
    case JUMPING:
        frameRect=jumpRects[currentFrame];
        break;
    }
    QPixmap currentFramePixmap=spriteSheet.copy(frameRect);
    currentFramePixmap=currentFramePixmap.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    if(!facingRight){
        currentFramePixmap=currentFramePixmap.transformed(QTransform().scale(-1, 1));
    }
    setPixmap(currentFramePixmap);
}
