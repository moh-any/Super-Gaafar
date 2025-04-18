#include "maingamewindow.h"
#include "ui_maingamewindow.h"
#include "coin.h"
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
#include <QRandomGenerator>
#include "powerup.h"



MainGameWindow::MainGameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainGameWindow)
{
    ui->setupUi(this);
    setWindowTitle("Super Gaafar");
    setFixedSize(900,650);
    setupGame();
    gameTimer=new QTimer(this);
    connect(gameTimer,&QTimer::timeout,this,&MainGameWindow::updateGame);
    gameTimer->start(15);
}

MainGameWindow::~MainGameWindow()
{
    delete ui;
}

void MainGameWindow::setupGame(){
    gameScene=new QGraphicsScene(this);
    gameScene->setSceneRect(0,0,2000,600);

    player=new Player();
    gameScene->addItem(player);
    player->setSceneWidth(2000);

    ground=new Ground();
    gameScene->addItem(ground);


    bg=new Background();
    gameScene->addItem(bg);

    bg->setZValue(1);
    ground->setZValue(2);
    player->setZValue(3);

    gameView=new QGraphicsView(gameScene,this);
    gameView->installEventFilter(this);

    gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    statusBar()->hide();
    setCentralWidget(gameView);



    Coin* coin = new Coin();
    coin->setPos(300, 500);
    gameScene->addItem(coin);
    coin->setZValue(3);

    coinSound = new QSoundEffect(this);
    coinSound->setSource(QUrl("qrc:/sounds/coin.wav"));
    coinSound->setVolume(0.25);


    powerupTimer = new QTimer(this);
    connect(powerupTimer, &QTimer::timeout, this, &MainGameWindow::spawnPowerUp);
    powerupTimer->start(2000); // Spawns a powerup every n seconds


}


void MainGameWindow::keyPressEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_Left){
        player->moveLeft();
    }
    else if(event->key()==Qt::Key_Right){
        player->moveRight();
    }
    else if(event->key()==Qt::Key_Space || event->key()==Qt::Key_Up){
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
    QList<QGraphicsItem*> colliding = player->collidingItems(Qt::IntersectsItemBoundingRect);
    for(auto item:colliding){
        Coin* coin=dynamic_cast<Coin*>(item);
        if(coin){
            coinSound->play();
            gameScene->removeItem(coin);
            delete coin;
        }
        PowerUp* powerUp = dynamic_cast<PowerUp*>(item);
        if (powerUp) {

            applyPowerUp(powerUp->getType());
            coinSound->play(); // until we get power ups sounds

            gameScene->removeItem(powerUp);
            delete powerUp;
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

void MainGameWindow::spawnPowerUp() {
    PowerUpType type = static_cast<PowerUpType>(QRandomGenerator::global()->bounded(3));
    PowerUp* powerup = new PowerUp(type);
    int x = QRandomGenerator::global()->bounded(gameScene->width() - 50);
    int y = QRandomGenerator::global()->bounded(400, 550);
    powerup->setPos(x, y);
    powerup->setZValue(3);
    gameScene->addItem(powerup);
}

void MainGameWindow::applyPowerUp(PowerUpType type) {
    switch (type) {
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
