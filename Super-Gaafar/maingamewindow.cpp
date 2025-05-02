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
#include "menu.h"

MainGameWindow::MainGameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainGameWindow)
{
    ui->setupUi(this);
    setWindowTitle("Super Gaafar");
    setFixedSize(900,650);

    PlatformsNum = 6;
    ObstaclesNum = 5;
    EnemiesNum= 4;
    platforms.clear();
    platforms.reserve(PlatformsNum);
    obstacles.clear();
    obstacles.reserve(ObstaclesNum);

    //setupGame();
    setupLevelOne();
    gameTimer=new QTimer(this);
    connect(gameTimer,&QTimer::timeout,this,&MainGameWindow::updateGame);
    gameTimer->start(15);

    themeSong = new QSoundEffect(this);
    themeSong->setSource(QUrl("qrc:/sounds/ThemeSong.wav"));
    themeSong->setVolume(0.75);
    themeSong->setLoopCount(QSoundEffect::Infinite);
    themeSong->play();
}

MainGameWindow::~MainGameWindow()
{
    delete ui;
}

// void MainGameWindow::setupGame(){
//     gameScene=new QGraphicsScene(this);
//     gameScene->setSceneRect(0,0,5000,600);

//     player=new Player();
//     gameScene->addItem(player);
//     player->setSceneWidth(5000);

//     ground=new Ground();
//     gameScene->addItem(ground);


//     bg=new Background();
//     gameScene->addItem(bg);

//     bg->setZValue(1);
//     ground->setZValue(2);
//     player->setZValue(3);

//     //manual
//     auto *p1 = new Platform(500, 400, "brick", 2);
//     auto *p2 = new Platform(1000, 400, "brick", 2);
//     auto *p3 = new Platform(1700, 400, "brick", 4);
//     auto *p4 = new Platform(2600, 400, "brick", 3);
//     auto *p5 = new Platform(3200, 400, "brick", 2);
//     auto *p6 = new Platform(4000, 400, "brick", 3);

//     gameScene->addItem(p1);
//     gameScene->addItem(p2);
//     gameScene->addItem(p3);
//     gameScene->addItem(p4);
//     gameScene->addItem(p5);
//     gameScene->addItem(p6);

//     p1->setZValue(3);
//     p2->setZValue(3);
//     p3->setZValue(3);
//     p4->setZValue(3);
//     p5->setZValue(3);
//     p6->setZValue(3);


//     //manual
//     auto *o1 = new Platform(700, 465, "warp");
//     auto *o2 = new Platform(1200, 465, "warp");
//     auto *o3 = new Platform(2300, 465, "warp");
//     auto *o4 = new Platform(3000, 465, "warp");
//     auto *o5 = new Platform(3700, 465, "warp");

//     gameScene->addItem(o1);
//     gameScene->addItem(o2);
//     gameScene->addItem(o3);
//     gameScene->addItem(o4);
//     gameScene->addItem(o5);

//     o1->setZValue(3);
//     o2->setZValue(3);
//     o3->setZValue(3);
//     o4->setZValue(3);
//     o5->setZValue(3);


//     auto *e1 = new Enemy(1000);
//     auto *e2 = new Enemy(1800);
//     auto *e3 = new Enemy(2900);
//     auto *e4 = new Enemy(3100);

//     enemies.append(e1);
//     enemies.append(e2);
//     enemies.append(e3);
//     enemies.append(e4);

//     gameScene->addItem(e1);
//     gameScene->addItem(e2);
//     gameScene->addItem(e3);
//     gameScene->addItem(e4);

//     e1->setZValue(3);
//     e2->setZValue(3);
//     e3->setZValue(3);
//     e4->setZValue(3);

//     gameView=new QGraphicsView(gameScene,this);
//     gameView->installEventFilter(this);
//     gameView->setRenderHint(QPainter::Antialiasing);

//     gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//     gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//     statusBar()->hide();
//     setCentralWidget(gameView);

//     Coin* coin1 = new Coin();
//     Coin* coin2 = new Coin();
//     Coin* coin3 = new Coin();
//     Coin* coin4 = new Coin();
//     Coin* coin5 = new Coin();
//     Coin* coin6 = new Coin();

//     coin1->setPos(300, 500);
//     coin2->setPos(320, 500);
//     coin4->setPos(1000, 500);
//     coin5->setPos(1750, 365);
//     coin6->setPos(1900, 500);
//     coin3->setPos(2315, 420);

//     gameScene->addItem(coin1);
//     gameScene->addItem(coin2);
//     gameScene->addItem(coin3);
//     gameScene->addItem(coin4);
//     gameScene->addItem(coin5);
//     gameScene->addItem(coin6);

//     coin1->setZValue(3);
//     coin2->setZValue(3);
//     coin3->setZValue(3);
//     coin4->setZValue(3);
//     coin5->setZValue(3);
//     coin6->setZValue(3);

//     Pole* pole=new Pole();
//     pole->setPos(5000-350,365);
//     gameScene->addItem(pole);
//     pole->setZValue(2);

//     Castle* castle=new Castle();
//     castle->setPos(5000-230,370);
//     gameScene->addItem(castle);
//     castle->setZValue(2);

//     coinSound = new QSoundEffect(this);
//     coinSound->setSource(QUrl("qrc:/sounds/coin.wav"));
//     coinSound->setVolume(0.75);

//     PowerUp* powerup1 = new PowerUp(Gigantification);
//     powerup1->setPos(2000, 520);
//     powerup1->setZValue(3);
//     gameScene->addItem(powerup1);

//     PowerUp* powerup2 = new PowerUp(SpeedBoost);

//     powerup2->setPos(1550, 520);
//     powerup2->setZValue(3);
//     gameScene->addItem(powerup2);

//     PowerUp* powerup3 = new PowerUp(JumpBoost);

//     powerup3->setPos(525, 365);
//     powerup3->setZValue(3);
//     gameScene->addItem(powerup3);
// }


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
    for(auto item : colliding){
        Coin* coin=dynamic_cast<Coin*>(item);
        if(coin){
            coinSound->play();
            gameScene->removeItem(item);
            delete item;
        }
        if(dynamic_cast<Pole*>(item)&& !reachedPole){
            reachedPole=true;
            qDebug() << "flag";
            flag=new Flag();
            flag->setPos(5000-325,500);
            gameScene->addItem(flag);
            flag->setZValue(2);
        }
        if(dynamic_cast<Castle*>(item)){
            gameScene->removeItem(player);
            victorySong = new QSoundEffect(this);
            victorySong->setSource(QUrl("qrc:/sounds/victory.wav"));
            victorySong->setVolume(0.75);
            themeSong->stop();
            victorySong->play();

            connect(victorySong, &QSoundEffect::playingChanged, this, [=]() {
                if (!victorySong->isPlaying()) {
                    returnToMainMenu();
                }
            });
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

            connect(deathSong, &QSoundEffect::playingChanged, this, [=]() {
                if (!deathSong->isPlaying()) {
                    returnToMainMenu();
                }
            });
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

void MainGameWindow::returnToMainMenu() {
    Menu* menu = new Menu();
    menu->show();
    this->close();
}


void MainGameWindow::setupLevelOne() {
    // This is just your existing setupGame() function, renamed and extracted.
    gameScene = new QGraphicsScene(this);
    gameScene->setSceneRect(0, 0, 5000, 600);

    player = new Player();
    gameScene->addItem(player);
    player->setSceneWidth(5000);

    ground = new Ground();
    gameScene->addItem(ground);

    bg = new Background();
    gameScene->addItem(bg);

    bg->setZValue(1);
    ground->setZValue(2);
    player->setZValue(3);

    // --- Platforms ---
    platforms = {
        new Platform(500, 400, "brick", 2),
        new Platform(1000, 400, "brick", 2),
        new Platform(1700, 400, "brick", 4),
        new Platform(2600, 400, "brick", 3),
        new Platform(3200, 400, "brick", 2),
        new Platform(4000, 400, "brick", 3)
    };
    for (auto* p : platforms) {
        gameScene->addItem(p);
        p->setZValue(3);
    }

    // --- Obstacles ---
    obstacles = {
        new Platform(700, 465, "warp"),
        new Platform(1200, 465, "warp"),
        new Platform(2300, 465, "warp"),
        new Platform(3000, 465, "warp"),
        new Platform(3700, 465, "warp")
    };
    for (auto* o : obstacles) {
        gameScene->addItem(o);
        o->setZValue(3);
    }

    // --- Enemies ---
    enemies = {
        new Enemy(1000),
        new Enemy(1800),
        new Enemy(2900),
        new Enemy(3100)
    };
    for (auto* e : enemies) {
        gameScene->addItem(e);
        e->setZValue(3);
    }

    // --- Game View ---
    gameView = new QGraphicsView(gameScene, this);
    gameView->installEventFilter(this);
    gameView->setRenderHint(QPainter::Antialiasing);
    gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    statusBar()->hide();
    setCentralWidget(gameView);

    // --- Coins ---
    QVector<QPointF> coinPositions = {
        {290, 500}, {320, 500},{350, 500}, {380, 500},
        {2315, 420},{2345, 420},{2375, 420},{2405, 420},
        {1000, 500}, {1030, 500},{1060, 500},{1090, 500},
        {1750, 365}, {1780, 365}, {1210, 365}, {1240, 365},
        {1900, 500}, {1930, 500},{1960, 500},{1990, 500}
    };

    for (const QPointF& pos : coinPositions) {
        Coin* coin = new Coin();
        coin->setPos(pos);
        coin->setZValue(3);
        gameScene->addItem(coin);
    }

    // --- Pole & Castle ---
    Pole* pole = new Pole();
    pole->setPos(5000 - 350, 365);
    pole->setZValue(2);
    gameScene->addItem(pole);

    Castle* castle = new Castle();
    castle->setPos(5000 - 230, 370);
    castle->setZValue(2);
    gameScene->addItem(castle);

    // --- PowerUps ---
    QVector<QPair<QPointF, PowerUpType>> powerUps = {
        {{2000, 520}, Gigantification},
        {{1550, 520}, SpeedBoost},
        {{525, 365}, JumpBoost}
    };
    for (auto& [pos, type] : powerUps) {
        PowerUp* p = new PowerUp(type);
        p->setPos(pos);
        p->setZValue(3);
        gameScene->addItem(p);
    }

    // --- Sounds ---
    coinSound = new QSoundEffect(this);
    coinSound->setSource(QUrl("qrc:/sounds/coin.wav"));
    coinSound->setVolume(0.75);
}

void MainGameWindow::setupLevelTwo() {
    // TODO: Implement Level 2
}

void MainGameWindow::setupLevelThree() {
    // TODO: Implement Level 3
}

void MainGameWindow::setupLevelFour() {
    // TODO: Implement Level 4
}

void MainGameWindow::setupLevelFive() {
    // TODO: Implement Level 5
}

