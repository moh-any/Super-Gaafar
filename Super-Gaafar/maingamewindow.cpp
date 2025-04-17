#include "maingamewindow.h"
#include "ui_maingamewindow.h"
#include "coin.h"
#include <QWidget>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QEvent>
#include <QRandomGenerator>
#include <QSoundEffect>


MainGameWindow::MainGameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainGameWindow)
{
    ui->setupUi(this);
    setWindowTitle("Super Gaafar");
    resize(1000,800);
    setupGame();
    gameTimer=new QTimer(this);
    connect(gameTimer,&QTimer::timeout,this,&MainGameWindow::updateGame);
    gameTimer->start(10);

}

MainGameWindow::~MainGameWindow()
{
    delete ui;
}

void MainGameWindow::setupGame(){
    gameScene=new QGraphicsScene(this);
    gameScene->setSceneRect(0,0,800,600);
    gameView=new QGraphicsView(gameScene,this);
    gameView->installEventFilter(this);
    setCentralWidget(gameView);

    player=new Player();
    gameScene->addItem(player);

    score = new QGraphicsTextItem;
    score->setFont (QFont("times", 16));
    score->setDefaultTextColor(Qt::black);
    score->setPlainText("Score: 0");
    score->setPos(0, 0); gameScene->addItem(score);

    Coin* coin = new Coin();
    coin->setPos(300, 500);
    gameScene->addItem(coin);

    coinTimer = new QTimer(this);
    connect(coinTimer, &QTimer::timeout, this, &MainGameWindow::spawnCoin);
    coinTimer->start(2000); // spawn a coin every n seconds

    coinSound = new QSoundEffect(this);
    coinSound->setSource(QUrl("qrc:/sounds/coin.wav"));
    coinSound->setVolume(0.25f); //volume from 0.0 to 1.0


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
    player->applyGravity();

    QList<QGraphicsItem*> colliding = player->collidingItems();
    for (QGraphicsItem* item : colliding) {
        Coin* coin = dynamic_cast<Coin*>(item);
        if (coin) {
            // Increase player's score
            player->increaseScore(10);

            // Update score label
            score->setPlainText("Score: " + QString::number(player->getScore()));

            // To play the coin sound when collected!
            coinSound->play();

            // Remove and delete coin
            gameScene->removeItem(coin);
            delete coin;
        }
    }

}


void MainGameWindow::spawnCoin() {
    int sceneWidth = gameScene->sceneRect().width();
    int sceneHeight = gameScene->sceneRect().height();

    int x = QRandomGenerator::global()->bounded(sceneWidth - 50); // Leave margin
    int y = QRandomGenerator::global()->bounded(sceneHeight - 200, sceneHeight); // Above ground level

    Coin* coin = new Coin();
    coin->setPos(x, y);
    gameScene->addItem(coin);
}
