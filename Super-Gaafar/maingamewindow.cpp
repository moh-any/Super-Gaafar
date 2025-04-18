#include "maingamewindow.h"
#include "ui_maingamewindow.h"
#include <QWidget>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QEvent>
#include <QPixmap>
#include <ground.h>
#include <background.h>
#include <coin.h>
#include <pole.h>
#include <castle.h>
#include <flag.h>
#include <powerup.h>
#include <enemy.h>
#include <QRandomGenerator>

MainGameWindow::MainGameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainGameWindow)
{
    ui->setupUi(this);
    setWindowTitle("Super Gaafar");
    setFixedSize(900,650);

    PlatformsNum = 10;
    ObstaclesNum = 10;
    EnemiesNum=10;
    platforms.clear();
    platforms.reserve(PlatformsNum);
    obstacles.clear();
    obstacles.reserve(ObstaclesNum);

    setupGame();
    gameTimer=new QTimer(this);
    connect(gameTimer,&QTimer::timeout,this,&MainGameWindow::updateGame);
    gameTimer->start(15);

    themeSong = new QSoundEffect(this);
    themeSong->setSource(QUrl("qrc:/sounds/ThemeSong.wav"));
    themeSong->setVolume(0.7);
    themeSong->setLoopCount(QSoundEffect::Infinite);
    // themeSong->play();
}

MainGameWindow::~MainGameWindow()
{
    delete ui;
}

void MainGameWindow::setupGame(){
    gameScene=new QGraphicsScene(this);
    gameScene->setSceneRect(0,0,10000,600);

    player=new Player();
    gameScene->addItem(player);
    player->setSceneWidth(10000);

    ground=new Ground();
    gameScene->addItem(ground);


    bg=new Background();
    gameScene->addItem(bg);

    bg->setZValue(1);
    ground->setZValue(2);
    player->setZValue(3);

    for (int i = 0; i < PlatformsNum; i++){
        auto *p = new Platform(1000*(i+1), 360, "brick",5);
        platforms.append(p);
        gameScene->addItem(platforms[i]);
        platforms[i]->setZValue(3);
    }

    for (int i = 0; i < ObstaclesNum; i++){
        auto *o = new Platform(1500*(i+1), 465, "warp");
        obstacles.append(o);
        gameScene->addItem(obstacles[i]);
        obstacles[i]->setZValue(3);
    }

    for (int i = 0; i < EnemiesNum; i++){
        auto *e = new Enemy(1200*(i+1));
        enemies.append(e);
        gameScene->addItem(enemies[i]);
        enemies[i]->setZValue(3);
    }
    gameView=new QGraphicsView(gameScene,this);
    gameView->installEventFilter(this);
    gameView->setRenderHint(QPainter::Antialiasing);

    gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    statusBar()->hide();
    setCentralWidget(gameView);

    Coin* coin = new Coin();
    coin->setPos(300, 500);
    gameScene->addItem(coin);
    coin->setZValue(3);

    Pole* pole=new Pole();
    pole->setPos(10000-350,365);
    gameScene->addItem(pole);
    pole->setZValue(2);

    Castle* castle=new Castle();
    castle->setPos(10000-230,370);
    gameScene->addItem(castle);
    castle->setZValue(2);

    coinSound = new QSoundEffect(this);
    coinSound->setSource(QUrl("qrc:/sounds/coin.wav"));
    coinSound->setVolume(0.25);

    PowerUp* powerup1 = new PowerUp(Gigantification);
    int x = QRandomGenerator::global()->bounded(gameScene->width() - 500);
    int y = QRandomGenerator::global()->bounded(400, 500);
    powerup1->setPos(x, y);
    powerup1->setZValue(3);
    gameScene->addItem(powerup1);

    PowerUp* powerup2 = new PowerUp(SpeedBoost);
    x = QRandomGenerator::global()->bounded(gameScene->width() - 500);
    y = QRandomGenerator::global()->bounded(400, 500);
    powerup2->setPos(x, y);
    powerup2->setZValue(3);
    gameScene->addItem(powerup2);

    PowerUp* powerup3 = new PowerUp(JumpBoost);
    x = QRandomGenerator::global()->bounded(gameScene->width() - 500);
    y = QRandomGenerator::global()->bounded(400, 500);
    powerup3->setPos(x, y);
    powerup3->setZValue(3);
    gameScene->addItem(powerup3);

}


void MainGameWindow::keyPressEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_Left){
        player->moveLeft();
    }
    else if(event->key()==Qt::Key_Right){
        player->moveRight();
    }
    else if(event->key()==Qt::Key_Space){
        player->jump();
    }
}

void MainGameWindow::keyReleaseEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_Left || event->key()==Qt::Key_Right) player->stopMoving();
}

bool MainGameWindow::eventFilter(QObject *object,QEvent *event){
    if(event->type()==QEvent::KeyPress){
        keyPressEvent((QKeyEvent*)event);
        return true;
    }
    else if(event->type()==QEvent::KeyRelease){
        keyReleaseEvent((QKeyEvent*)event);
        return true;
    }
    else return QObject::eventFilter(object, event);
}
void MainGameWindow::updateGame(){
    player->update();
    gameView->centerOn(player->pos());
    for (auto enemy : enemies){
        enemy->move();
    }
    QList<QGraphicsItem*> colliding = player->collidingItems(Qt::IntersectsItemBoundingRect);
    for(auto item:colliding){
        if(dynamic_cast<Coin*>(item)){
            coinSound->play();
            gameScene->removeItem(item);
            delete item;
        }
        if(dynamic_cast<Pole*>(item)&& !reachedPole){
            reachedPole=true;
            qDebug() << "flag";
            flag=new Flag();
            flag->setPos(10000-325,500);
            gameScene->addItem(flag);
            flag->setZValue(2);
        }
        if(dynamic_cast<Castle*>(item)){
            gameScene->removeItem(player);
            victorySong = new QSoundEffect(this);
            victorySong->setSource(QUrl("qrc:/sounds/victory.wav"));
            victorySong->setVolume(0.25);
            themeSong->stop();
            victorySong->play();
        }
        if(dynamic_cast<PowerUp*>(item)){
            applyPowerUp(((PowerUp*)item)->getType());
            coinSound->play(); // until we get power ups sounds
            gameScene->removeItem(item);
            delete item;
        }
        if(dynamic_cast<Enemy*>(item)){
            gameScene->removeItem(player);
            deathSong = new QSoundEffect(this);
            deathSong->setSource(QUrl("qrc:/sounds/death.wav"));
            deathSong->setVolume(0.25);
            themeSong->stop();
            deathSong->play();
        }
        Platform *platform = dynamic_cast<Platform *> (item);
        if (platform && player->getFacingRight()){
            player->setPos(platform->pos().x()-player->boundingRect().width()+5,player->pos().y());
        }
        else if(platform && !player->getFacingRight()){
            player->setPos(platform->pos().x()+platform->boundingRect().width(),player->pos().y());
        }
    }
}

void MainGameWindow::spawnCoin() {
    int sceneWidth = gameScene->sceneRect().width();
    int sceneHeight = gameScene->sceneRect().height();
    int x = QRandomGenerator::global()->bounded(sceneWidth - 50);
    int y = QRandomGenerator::global()->bounded(sceneHeight - 200, sceneHeight);
    Coin* coin = new Coin();
    coin->setPos(x, y);
    gameScene->addItem(coin);
}

void MainGameWindow::applyPowerUp(PowerUpType type){
    switch(type){
    case SpeedBoost:
        player->setMovementSpeed(10.0);
        QTimer::singleShot(5000, [=]() { player->setMovementSpeed(5.0); });
        break;
    case JumpBoost:
        player->setJumpForce(20.0);
        QTimer::singleShot(5000, [=]() { player->setJumpForce(15.0); });
        break;
    case Gigantification:
        player->applyGiantPowerUp();
        break;
    }
}
