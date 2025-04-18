#include "maingamewindow.h"
#include "ui_maingamewindow.h"
#include "coin.h"
#include "enemy.h"
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
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

MainGameWindow::MainGameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainGameWindow)
{
    ui->setupUi(this);
    setWindowTitle("Super Gaafar");
    setFixedSize(900,650);

    gameTimer=new QTimer(this);
    connect(gameTimer,&QTimer::timeout,this,&MainGameWindow::updateGame);
    gameTimer->start(15);

    PlatformsNum = 10;
    ObstaclesNum = 10;
    EnemiesNum = 10;
    platforms.clear();
    platforms.reserve(PlatformsNum);
    obstacles.clear();
    obstacles.reserve(ObstaclesNum);
    enemies.clear();
    enemies.reserve(EnemiesNum);
    setupGame();
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

    //creating platforms
    for (int i = 0; i < PlatformsNum; i++){
        auto *p = new Platform(1000*(i+1), 360, "brick");
        platforms.append(p);
        gameScene->addItem(platforms[i]);
        platforms[i]->setZValue(3);
    }

    //creating obstacles
    for (int i = 0; i < ObstaclesNum; i++){
        auto *o = new Platform(1500*(i+1), 465, "warp");
        obstacles.append(o);
        gameScene->addItem(obstacles[i]);
        obstacles[i]->setZValue(3);
    }

    //creating enemies
    for (int i = 0; i < EnemiesNum; i++){
        auto *e = new Enemy(1200*(i+1));
        enemies.append(e);
        gameScene->addItem(enemies[i]);
        enemies[i]->setZValue(3);
    }

    bg->setZValue(1);
    ground->setZValue(2);
    player->setZValue(4);

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
    for (auto enemy : enemies){
        enemy->move();
    }
    gameView->centerOn(player->pos());
    QList<QGraphicsItem*> colliding = player->collidingItems(Qt::IntersectsItemBoundingRect);
    for(int i = 0; i < colliding.size(); i++){
        Coin* coin=dynamic_cast<Coin*>(colliding[i]);
        Enemy* enemy=dynamic_cast<Enemy*>(colliding[i]);
        if(coin){
            coinSound->play();
            gameScene->removeItem(coin);
            delete coin;
        }
        else if (enemy){
            player->die();
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

