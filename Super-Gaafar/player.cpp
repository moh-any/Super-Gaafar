#include "player.h"
#include <QGraphicsScene>
#include <QRectF>
#include <QTransform>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QTimer>
#include <QObject>
Player::Player(QGraphicsItem *parent):QGraphicsPixmapItem(parent),facingRight(true),velocityX(0),movementSpeed(5.0),velocityY(0),gravity(0.5),isJumping(false),jumpForce(15.0),ground(600){
    sprite=QPixmap(":/images/supermario.png");
    sprite=sprite.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setPixmap(sprite);
    setPos(800,ground);
    jumpTimer=new QTimer(this);
    connect(jumpTimer,&QTimer::timeout,this,&Player::applyGravity);
    jumpTimer->start(20);
}

void Player::moveLeft(){
    velocityX=-movementSpeed;
    if(facingRight){
        QPixmap flippedSprite=sprite.transformed(QTransform().scale(-1, 1));
        setPixmap(flippedSprite);
        facingRight=false;
    }
}

void Player::moveRight(){
    velocityX=movementSpeed;
    if(!facingRight) {
        setPixmap(sprite);
        facingRight=true;
    }
}

void Player::stopMoving(){
    velocityX=0;
}

void Player::jump(){
    if(!isJumping){
        isJumping=true;
        velocityY=-jumpForce;
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
}

void Player::applyGravity(){
    velocityY+=gravity;
    setPos(pos().x(),pos().y()+velocityY);
    if(pos().y()>=ground){
        setPos(pos().x(),ground);
        velocityY=0;
        isJumping=false;
    }
}
