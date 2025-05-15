#include "maingamewindow.h"
#include "ui_maingamewindow.h"
#include "levelselection.h"
#include <QWidget>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QEvent>

MainGameWindow::MainGameWindow(QWidget *parent, int startLevel)
    : QMainWindow(parent)
    , ui(new Ui::MainGameWindow)
{
    ui->setupUi(this);
    setWindowTitle("Super Gaafar");
    setFixedSize(900,650);
    this->setStyleSheet("background-color: #b7f7b3;");
    PlatformsNum = 6;
    ObstaclesNum = 5;
    EnemiesNum= 4;
    platforms.clear();
    platforms.reserve(PlatformsNum);
    obstacles.clear();
    obstacles.reserve(ObstaclesNum);
    setupGame(startLevel);
    gameTimer=new QTimer(this);
    connect(gameTimer,&QTimer::timeout,this,&MainGameWindow::updateGame);
    gameTimer->start(15);
    themeSong = new QSoundEffect(this);
    themeSong->setSource(QUrl("qrc:/sounds/sounds/ThemeSong.wav"));
    themeSong->setVolume(0.75);
    themeSong->setLoopCount(QSoundEffect::Infinite);
    themeSong->play();
}

MainGameWindow::~MainGameWindow()
{
    delete ui;
}

void MainGameWindow::setupGame(int startLevel){
    levelCompleted = false;
    gameScene=new QGraphicsScene(this);
    gameScene->setSceneRect(0,0,5000,600);
    player=new Player();
    gameScene->addItem(player);
    player->setSceneWidth(5000);
    ground=new Ground();
    gameScene->addItem(ground);
    bg=new Background();
    gameScene->addItem(bg);
    bg->setZValue(1);
    ground->setZValue(2);
    player->setZValue(3);
    currentLevel = startLevel;
    switch (currentLevel) {
        case 1:
            level1Setup();
            break;
        case 2:
            level2Setup();
            break;
        case 3:
            level3Setup();
            break;
        case 4:
            level4Setup();
            break;
        case 5:
            level5Setup();
            break;
        default:
            level1Setup();
            break;
    }
    gameView=new QGraphicsView(gameScene,this);
    gameView->installEventFilter(this);
    gameView->setRenderHint(QPainter::Antialiasing);
    gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    statusBar()->hide();
    setCentralWidget(gameView);
    gameView->show();
    coinSound = new QSoundEffect(this);
    coinSound->setSource(QUrl("qrc:/sounds/sounds/coin.wav"));
    coinSound->setVolume(0.75);
    powerupSound = new QSoundEffect(this);
    powerupSound->setSource(QUrl("qrc:/sounds/sounds/powerup.wav"));
    powerupSound->setVolume(0.5);
    levelCompletedSound = new QSoundEffect(this);
    levelCompletedSound->setSource(QUrl("qrc:/sounds/sounds/levelclear.wav"));
    levelCompletedSound->setVolume(0.75);
    scoreText = new QGraphicsTextItem();
    scoreText->setFont(QFont("Arial", 18, QFont::Bold));
    scoreText->setDefaultTextColor(Qt::black);
    scoreText->setZValue(100);
    scoreText->setPos(20, 10);
    livesText = new QGraphicsTextItem();
    livesText->setDefaultTextColor(Qt::black);
    livesText->setFont(QFont("Arial", 18, QFont::Bold));
    livesText->setZValue(100);
    livesText->setPos(20, 40);
    levelText = new QGraphicsTextItem();
    levelText->setDefaultTextColor(Qt::black);
    levelText->setFont(QFont("Arial", 18, QFont::Bold));
    levelText->setZValue(100);
    levelText->setPos(20, 70);
    hudScene = new QGraphicsScene(this);
    hudScene->addItem(scoreText);
    hudScene->addItem(livesText);
    hudScene->addItem(levelText);
    hudView = new QGraphicsView(hudScene, gameView);
    hudView->setStyleSheet("background: transparent");
    hudView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    hudView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    hudView->setFrameShape(QFrame::NoFrame);
    hudView->setFixedSize(200, 100);
    hudView->setGeometry(10, 10, 200, 100);
    hudView->show();
    updateHUD();
}

void MainGameWindow::level1Setup() {
    auto *p1 = new Platform(500, 400, "brick", 2);
    auto *p2 = new Platform(1000, 400, "brick", 2);
    auto *p3 = new Platform(1700, 400, "brick", 4);
    auto *p4 = new Platform(2600, 400, "brick", 3);
    auto *p5 = new Platform(3200, 400, "brick", 2);
    auto *p6 = new Platform(4000, 400, "brick", 3);
    gameScene->addItem(p1);
    gameScene->addItem(p2);
    gameScene->addItem(p3);
    gameScene->addItem(p4);
    gameScene->addItem(p5);
    gameScene->addItem(p6);
    p1->setZValue(3);
    p2->setZValue(3);
    p3->setZValue(3);
    p4->setZValue(3);
    p5->setZValue(3);
    p6->setZValue(3);
    auto *o1 = new Platform(700, 465, "warp");
    auto *o2 = new Platform(1200, 465, "warp");
    auto *o3 = new Platform(2300, 465, "warp");
    auto *o4 = new Platform(3000, 465, "warp");
    auto *o5 = new Platform(3700, 465, "warp");
    gameScene->addItem(o1);
    gameScene->addItem(o2);
    gameScene->addItem(o3);
    gameScene->addItem(o4);
    gameScene->addItem(o5);
    o1->setZValue(3);
    o2->setZValue(3);
    o3->setZValue(3);
    o4->setZValue(3);
    o5->setZValue(3);
    RedT *e1 = new RedT(3100);
    RedT *e3 = new RedT(2900);
    Spiny *e4 = new Spiny(1000);
    Goomba *e2 = new Goomba(1800);
    enemies.append(e1);
    enemies.append(e2);
    enemies.append(e3);
    enemies.append(e4);
    gameScene->addItem(e1);
    gameScene->addItem(e2);
    gameScene->addItem(e3);
    gameScene->addItem(e4);
    e1->setZValue(3);
    e2->setZValue(3);
    e3->setZValue(3);
    e4->setZValue(3);
    Coin* coin1 = new Coin();
    Coin* coin2 = new Coin();
    Coin* coin3 = new Coin();
    Coin* coin4 = new Coin();
    Coin* coin5 = new Coin();
    Coin* coin6 = new Coin();
    coin1->setPos(300, 500);
    coin2->setPos(320, 500);
    coin4->setPos(1000, 500);
    coin5->setPos(1750, 365);
    coin6->setPos(1900, 500);
    coin3->setPos(2315, 420);
    gameScene->addItem(coin1);
    gameScene->addItem(coin2);
    gameScene->addItem(coin3);
    gameScene->addItem(coin4);
    gameScene->addItem(coin5);
    gameScene->addItem(coin6);
    coin1->setZValue(3);
    coin2->setZValue(3);
    coin3->setZValue(3);
    coin4->setZValue(3);
    coin5->setZValue(3);
    coin6->setZValue(3);
    Pole* pole = new Pole();
    pole->setPos(5000-350, 365);
    gameScene->addItem(pole);
    pole->setZValue(2);
    Castle* castle = new Castle();
    castle->setPos(5000-230, 370);
    gameScene->addItem(castle);
    castle->setZValue(2);
    PowerUp* powerup1 = new PowerUp(Gigantification);
    powerup1->setPos(2000, 520);
    powerup1->setZValue(3);
    gameScene->addItem(powerup1);
    PowerUp* powerup2 = new PowerUp(SpeedBoost);
    powerup2->setPos(1550, 520);
    powerup2->setZValue(3);
    gameScene->addItem(powerup2);
    PowerUp* powerup3 = new PowerUp(JumpBoost);
    powerup3->setPos(525, 365);
    powerup3->setZValue(3);
    gameScene->addItem(powerup3);
}

void MainGameWindow::level2Setup() {
    auto *p1 = new Platform(400, 350, "brick", 2);
    auto *p2 = new Platform(900, 300, "brick", 3);
    auto *p3 = new Platform(1500, 400, "brick", 2);
    auto *p4 = new Platform(2100, 320, "brick", 4);
    auto *p5 = new Platform(2700, 370, "brick", 3);
    auto *p6 = new Platform(3400, 420, "brick", 2);
    auto *p7 = new Platform(4200, 350, "brick", 3);
    gameScene->addItem(p1);
    gameScene->addItem(p2);
    gameScene->addItem(p3);
    gameScene->addItem(p4);
    gameScene->addItem(p5);
    gameScene->addItem(p6);
    gameScene->addItem(p7);
    p1->setZValue(3);
    p2->setZValue(3);
    p3->setZValue(3);
    p4->setZValue(3);
    p5->setZValue(3);
    p6->setZValue(3);
    p7->setZValue(3);
    auto *o1 = new Platform(600, 465, "warp");
    auto *o2 = new Platform(1200, 465, "warp");
    auto *o3 = new Platform(1800, 465, "warp");
    auto *o4 = new Platform(2500, 465, "warp");
    auto *o5 = new Platform(3200, 465, "warp");
    auto *o6 = new Platform(3900, 465, "warp");
    auto *o7 = new Platform(4400, 465, "warp");
    gameScene->addItem(o1);
    gameScene->addItem(o2);
    gameScene->addItem(o3);
    gameScene->addItem(o4);
    gameScene->addItem(o5);
    gameScene->addItem(o6);
    gameScene->addItem(o7);
    o1->setZValue(3);
    o2->setZValue(3);
    o3->setZValue(3);
    o4->setZValue(3);
    o5->setZValue(3);
    o6->setZValue(3);
    o7->setZValue(3);
    RedT *e1 = new RedT(1000);
    RedT *e2 = new RedT(1600);
    Spiny *e3 = new Spiny(2200);
    Goomba *e4 = new Goomba(2800);
    Spiny *e5 = new Spiny(3500);
    Goomba *e6 = new Goomba(4100);
    RedT *e7 = new RedT(4700);
    Goomba *e8 = new Goomba(950);
    Spiny *e9 = new Spiny(2120);
    enemies.append(e1);
    enemies.append(e2);
    enemies.append(e3);
    enemies.append(e4);
    enemies.append(e5);
    enemies.append(e6);
    enemies.append(e7);
    enemies.append(e8);
    enemies.append(e9);
    gameScene->addItem(e1);
    gameScene->addItem(e2);
    gameScene->addItem(e3);
    gameScene->addItem(e4);
    gameScene->addItem(e5);
    gameScene->addItem(e6);
    gameScene->addItem(e7);
    gameScene->addItem(e8);
    gameScene->addItem(e9);
    e1->setZValue(3);
    e2->setZValue(3);
    e3->setZValue(3);
    e4->setZValue(3);
    e5->setZValue(3);
    e6->setZValue(3);
    e7->setZValue(3);
    e8->setZValue(3);
    e9->setZValue(3);
    Coin* coin1 = new Coin(); coin1->setPos(450, 300); gameScene->addItem(coin1); coin1->setZValue(3);
    Coin* coin2 = new Coin(); coin2->setPos(950, 250); gameScene->addItem(coin2); coin2->setZValue(3);
    Coin* coin3 = new Coin(); coin3->setPos(1550, 350); gameScene->addItem(coin3); coin3->setZValue(3);
    Coin* coin4 = new Coin(); coin4->setPos(2150, 270); gameScene->addItem(coin4); coin4->setZValue(3);
    Coin* coin5 = new Coin(); coin5->setPos(2750, 320); gameScene->addItem(coin5); coin5->setZValue(3);
    Coin* coin6 = new Coin(); coin6->setPos(3450, 370); gameScene->addItem(coin6); coin6->setZValue(3);
    Coin* coin7 = new Coin(); coin7->setPos(4050, 300); gameScene->addItem(coin7); coin7->setZValue(3);
    Coin* coin8 = new Coin(); coin8->setPos(4650, 250); gameScene->addItem(coin8); coin8->setZValue(3);
    Pole* pole = new Pole();
    pole->setPos(5000-350, 365);
    gameScene->addItem(pole);
    pole->setZValue(2);
    Castle* castle = new Castle();
    castle->setPos(5000-230, 370);
    gameScene->addItem(castle);
    castle->setZValue(2);
    PowerUp* powerup1 = new PowerUp(Gigantification);
    powerup1->setPos(2000, 520);
    powerup1->setZValue(3);
    gameScene->addItem(powerup1);
    PowerUp* powerup2 = new PowerUp(SpeedBoost);
    powerup2->setPos(1550, 520);
    powerup2->setZValue(3);
    gameScene->addItem(powerup2);
}

void MainGameWindow::level3Setup() {
    auto *p1 = new Platform(350, 420, "brick", 3);
    auto *p2 = new Platform(900, 350, "brick", 4);
    auto *p3 = new Platform(1550, 350, "brick", 3);
    auto *p4 = new Platform(2100, 320, "brick", 2);
    auto *p5 = new Platform(2650, 400, "brick", 3);
    auto *p6 = new Platform(3300, 350, "brick", 2);
    gameScene->addItem(p1); p1->setZValue(3);
    gameScene->addItem(p2); p2->setZValue(3);
    gameScene->addItem(p3); p3->setZValue(3);
    gameScene->addItem(p4); p4->setZValue(3);
    gameScene->addItem(p5); p5->setZValue(3);
    gameScene->addItem(p6); p6->setZValue(3);
    auto *o1 = new Platform(700, 465, "warp");
    auto *o3 = new Platform(1800, 465, "warp");
    auto *o4 = new Platform(2500, 465, "warp");
    auto *o5 = new Platform(3100, 465, "warp");
    auto *o6 = new Platform(3700, 465, "warp");
    auto *o7 = new Platform(4200, 465, "warp");
    gameScene->addItem(o1); o1->setZValue(3);
    gameScene->addItem(o3); o3->setZValue(3);
    gameScene->addItem(o4); o4->setZValue(3);
    gameScene->addItem(o5); o5->setZValue(3);
    gameScene->addItem(o6); o6->setZValue(3);
    gameScene->addItem(o7); o7->setZValue(3);
    Goomba *e1 = new Goomba(600);
    Spiny  *e2 = new Spiny(1150);
    RedT   *e3 = new RedT(1700);
    Goomba *e4 = new Goomba(2250);
    Spiny  *e5 = new Spiny(2950);
    RedT   *e6 = new RedT(3550);
    Goomba *e7 = new Goomba(4150);
    Spiny  *e8 = new Spiny(950);
    RedT   *e9 = new RedT(2100);
    Goomba *e10 = new Goomba(2650);
    Spiny  *e11 = new Spiny(3900);
    RedT   *e12 = new RedT(4450);
    enemies.append(e1); gameScene->addItem(e1); e1->setZValue(3);
    enemies.append(e2); gameScene->addItem(e2); e2->setZValue(3);
    enemies.append(e3); gameScene->addItem(e3); e3->setZValue(3);
    enemies.append(e4); gameScene->addItem(e4); e4->setZValue(3);
    enemies.append(e5); gameScene->addItem(e5); e5->setZValue(3);
    enemies.append(e6); gameScene->addItem(e6); e6->setZValue(3);
    enemies.append(e7); gameScene->addItem(e7); e7->setZValue(3);
    enemies.append(e8); gameScene->addItem(e8); e8->setZValue(3);
    enemies.append(e9); gameScene->addItem(e9); e9->setZValue(3);
    enemies.append(e10); gameScene->addItem(e10); e10->setZValue(3);
    enemies.append(e11); gameScene->addItem(e11); e11->setZValue(3);
    enemies.append(e12); gameScene->addItem(e12); e12->setZValue(3);
    Coin* coin1 = new Coin(); coin1->setPos(400, 370); gameScene->addItem(coin1); coin1->setZValue(3);
    Coin* coin2 = new Coin(); coin2->setPos(950, 300); gameScene->addItem(coin2); coin2->setZValue(3);
    Coin* coin3 = new Coin(); coin3->setPos(1550, 370); gameScene->addItem(coin3); coin3->setZValue(3);
    Coin* coin4 = new Coin(); coin4->setPos(2100, 270); gameScene->addItem(coin4); coin4->setZValue(3);
    Coin* coin5 = new Coin(); coin5->setPos(2650, 350); gameScene->addItem(coin5); coin5->setZValue(3);
    Coin* coin6 = new Coin(); coin6->setPos(3300, 300); gameScene->addItem(coin6); coin6->setZValue(3);
    Coin* coin7 = new Coin(); coin7->setPos(3900, 370); gameScene->addItem(coin7); coin7->setZValue(3);
    Coin* coin8 = new Coin(); coin8->setPos(4450, 270); gameScene->addItem(coin8); coin8->setZValue(3);
    Pole* pole = new Pole();
    pole->setPos(5000-350, 365);
    gameScene->addItem(pole);
    pole->setZValue(2);
    Castle* castle = new Castle();
    castle->setPos(5000-230, 370);
    gameScene->addItem(castle);
    castle->setZValue(2);
    PowerUp* powerup1 = new PowerUp(Gigantification);
    powerup1->setPos(1550, 520);
    powerup1->setZValue(3);
    gameScene->addItem(powerup1);
    PowerUp* powerup2 = new PowerUp(SpeedBoost);
    powerup2->setPos(3300, 520);
    powerup2->setZValue(3);
    gameScene->addItem(powerup2);
}

void MainGameWindow::level4Setup() {
    auto *p1 = new Platform(300, 420, "brick", 3);
    auto *p2 = new Platform(800, 350, "brick", 3);
    auto *p3 = new Platform(1400, 300, "brick", 3);
    auto *p4 = new Platform(1900, 400, "brick", 3);
    auto *p5 = new Platform(2500, 320, "brick", 3);
    auto *p6 = new Platform(3100, 370, "brick", 3);
    auto *p7 = new Platform(3700, 300, "brick", 3);
    gameScene->addItem(p1); p1->setZValue(3);
    gameScene->addItem(p2); p2->setZValue(3);
    gameScene->addItem(p3); p3->setZValue(3);
    gameScene->addItem(p4); p4->setZValue(3);
    gameScene->addItem(p5); p5->setZValue(3);
    gameScene->addItem(p6); p6->setZValue(3);
    gameScene->addItem(p7); p7->setZValue(3);
    auto *o1 = new Platform(600, 465, "warp");
    auto *o2 = new Platform(1200, 465, "warp");
    auto *o3 = new Platform(1800, 465, "warp");
    auto *o4 = new Platform(2400, 465, "warp");
    auto *o5 = new Platform(3000, 465, "warp");
    auto *o6 = new Platform(3600, 465, "warp");
    auto *o7 = new Platform(4200, 465, "warp");
    gameScene->addItem(o1); o1->setZValue(3);
    gameScene->addItem(o2); o2->setZValue(3);
    gameScene->addItem(o3); o3->setZValue(3);
    gameScene->addItem(o4); o4->setZValue(3);
    gameScene->addItem(o5); o5->setZValue(3);
    gameScene->addItem(o6); o6->setZValue(3);
    gameScene->addItem(o7); o7->setZValue(3);
    Goomba *e1 = new Goomba(500);
    Spiny  *e2 = new Spiny(1000);
    RedT   *e3 = new RedT(1700);
    Goomba *e4 = new Goomba(2300);
    Spiny  *e5 = new Spiny(2800);
    RedT   *e6 = new RedT(3500);
    Goomba *e7 = new Goomba(4100);
    Spiny  *e8 = new Spiny(4700);
    RedT   *e9 = new RedT(800);
    Goomba *e10 = new Goomba(1900);
    Spiny  *e11 = new Spiny(3150);
    enemies.append(e1); gameScene->addItem(e1); e1->setZValue(3);
    enemies.append(e2); gameScene->addItem(e2); e2->setZValue(3);
    enemies.append(e3); gameScene->addItem(e3); e3->setZValue(3);
    enemies.append(e4); gameScene->addItem(e4); e4->setZValue(3);
    enemies.append(e5); gameScene->addItem(e5); e5->setZValue(3);
    enemies.append(e6); gameScene->addItem(e6); e6->setZValue(3);
    enemies.append(e7); gameScene->addItem(e7); e7->setZValue(3);
    enemies.append(e8); gameScene->addItem(e8); e8->setZValue(3);
    enemies.append(e9); gameScene->addItem(e9); e9->setZValue(3);
    enemies.append(e10); gameScene->addItem(e10); e10->setZValue(3);
    enemies.append(e11); gameScene->addItem(e11); e11->setZValue(3);
    Coin* coin1 = new Coin(); coin1->setPos(350, 370); gameScene->addItem(coin1); coin1->setZValue(3);
    Coin* coin2 = new Coin(); coin2->setPos(800, 300); gameScene->addItem(coin2); coin2->setZValue(3);
    Coin* coin3 = new Coin(); coin3->setPos(1400, 250); gameScene->addItem(coin3); coin3->setZValue(3);
    Coin* coin4 = new Coin(); coin4->setPos(1900, 350); gameScene->addItem(coin4); coin4->setZValue(3);
    Coin* coin5 = new Coin(); coin5->setPos(2500, 270); gameScene->addItem(coin5); coin5->setZValue(3);
    Coin* coin6 = new Coin(); coin6->setPos(3100, 320); gameScene->addItem(coin6); coin6->setZValue(3);
    Coin* coin7 = new Coin(); coin7->setPos(3700, 250); gameScene->addItem(coin7); coin7->setZValue(3);
    Coin* coin8 = new Coin(); coin8->setPos(4200, 370); gameScene->addItem(coin8); coin8->setZValue(3);
    Coin* coin9 = new Coin(); coin9->setPos(4700, 300); gameScene->addItem(coin9); coin9->setZValue(3);
    Pole* pole = new Pole();
    pole->setPos(5000-350, 365);
    gameScene->addItem(pole);
    pole->setZValue(2);
    Castle* castle = new Castle();
    castle->setPos(5000-230, 370);
    gameScene->addItem(castle);
    castle->setZValue(2);
    PowerUp* powerup1 = new PowerUp(Gigantification);
    powerup1->setPos(1900, 520);
    powerup1->setZValue(3);
    gameScene->addItem(powerup1);
    PowerUp* powerup2 = new PowerUp(SpeedBoost);
    powerup2->setPos(3100, 520);
    powerup2->setZValue(3);
    gameScene->addItem(powerup2);
    PowerUp* powerup3 = new PowerUp(JumpBoost);
    powerup3->setPos(4100, 520);
    powerup3->setZValue(3);
    gameScene->addItem(powerup3);
}

void MainGameWindow::level5Setup() {
    auto *p1 = new Platform(200, 420, "brick", 2);
    auto *p2 = new Platform(800, 340, "brick", 2);
    auto *p4 = new Platform(1800, 400, "brick", 3);
    auto *p5 = new Platform(2400, 320, "brick", 2);
    auto *p6 = new Platform(3000, 370, "brick", 2);
    auto *p7 = new Platform(3600, 300, "brick", 2);
    auto *p8 = new Platform(4200, 420, "brick", 2);
    gameScene->addItem(p1); p1->setZValue(3);
    gameScene->addItem(p2); p2->setZValue(3);
    gameScene->addItem(p4); p4->setZValue(3);
    gameScene->addItem(p5); p5->setZValue(3);
    gameScene->addItem(p6); p6->setZValue(3);
    gameScene->addItem(p7); p7->setZValue(3);
    gameScene->addItem(p8); p8->setZValue(3);
    auto *o1 = new Platform(500, 465, "warp");
    auto *o2 = new Platform(1100, 465, "warp");
    auto *o3 = new Platform(1700, 465, "warp");
    auto *o4 = new Platform(2300, 465, "warp");
    auto *o5 = new Platform(2900, 465, "warp");
    auto *o6 = new Platform(3500, 465, "warp");
    gameScene->addItem(o1); o1->setZValue(3);
    gameScene->addItem(o2); o2->setZValue(3);
    gameScene->addItem(o3); o3->setZValue(3);
    gameScene->addItem(o4); o4->setZValue(3);
    gameScene->addItem(o5); o5->setZValue(3);
    gameScene->addItem(o6); o6->setZValue(3);
    Goomba *e1 = new Goomba(350);
    Spiny  *e2 = new Spiny(950);
    RedT   *e3 = new RedT(1250);
    Goomba *e4 = new Goomba(2000);
    Spiny  *e5 = new Spiny(2700);
    RedT   *e6 = new RedT(3200);
    Goomba *e7 = new Goomba(3900);
    Spiny  *e8 = new Spiny(800);
    RedT   *e9 = new RedT(1800);
    Goomba *e10 = new Goomba(3600);
    enemies.append(e1); gameScene->addItem(e1); e1->setZValue(3);
    enemies.append(e2); gameScene->addItem(e2); e2->setZValue(3);
    enemies.append(e3); gameScene->addItem(e3); e3->setZValue(3);
    enemies.append(e4); gameScene->addItem(e4); e4->setZValue(3);
    enemies.append(e5); gameScene->addItem(e5); e5->setZValue(3);
    enemies.append(e6); gameScene->addItem(e6); e6->setZValue(3);
    enemies.append(e7); gameScene->addItem(e7); e7->setZValue(3);
    enemies.append(e8); gameScene->addItem(e8); e8->setZValue(3);
    enemies.append(e9); gameScene->addItem(e9); e9->setZValue(3);
    enemies.append(e10); gameScene->addItem(e10); e10->setZValue(3);
    Coin* coin1 = new Coin(); coin1->setPos(300, 370); gameScene->addItem(coin1); coin1->setZValue(3);
    Coin* coin2 = new Coin(); coin2->setPos(900, 290); gameScene->addItem(coin2); coin2->setZValue(3);
    Coin* coin3 = new Coin(); coin3->setPos(1400, 210); gameScene->addItem(coin3); coin3->setZValue(3);
    Coin* coin4 = new Coin(); coin4->setPos(1800, 350); gameScene->addItem(coin4); coin4->setZValue(3);
    Coin* coin5 = new Coin(); coin5->setPos(2400, 270); gameScene->addItem(coin5); coin5->setZValue(3);
    Coin* coin6 = new Coin(); coin6->setPos(3000, 320); gameScene->addItem(coin6); coin6->setZValue(3);
    Coin* coin7 = new Coin(); coin7->setPos(3600, 250); gameScene->addItem(coin7); coin7->setZValue(3);
    Coin* coin8 = new Coin(); coin8->setPos(4200, 370); gameScene->addItem(coin8); coin8->setZValue(3);
    Pole* pole = new Pole();
    pole->setPos(5000-350, 365);
    gameScene->addItem(pole);
    pole->setZValue(2);
    Castle* castle = new Castle();
    castle->setPos(5000-230, 370);
    gameScene->addItem(castle);
    castle->setZValue(2);
    PowerUp* powerup1 = new PowerUp(Gigantification);
    powerup1->setPos(1800, 520);
    powerup1->setZValue(3);
    gameScene->addItem(powerup1);
    PowerUp* powerup2 = new PowerUp(SpeedBoost);
    powerup2->setPos(3000, 520);
    powerup2->setZValue(3);
    gameScene->addItem(powerup2);
}

void MainGameWindow::updateHUD() {
    if(scoreText) scoreText->setPlainText(QString("Score: ")+QString::number(score));
    if(livesText) livesText->setPlainText(QString("Lives: ")+QString::number(player->getLives()));
    if(levelText) levelText->setPlainText(QString("Level: ")+QString::number(currentLevel));
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
    updateHUD();
    bool collidingSidePlatform = false;
    bool landedOnPlatform = false;
    QList<QGraphicsItem*> colliding = player->collidingItems(Qt::IntersectsItemBoundingRect);
    for(auto item : colliding){
        Platform* platform = dynamic_cast<Platform*>(item);
        if(platform){
            QRectF playerRect = player->sceneBoundingRect();
            QRectF platRect = platform->sceneBoundingRect();
            if(player->getVelocityX() > 0 && playerRect.right() > platRect.left() && playerRect.left() < platRect.left() && playerRect.bottom() > platRect.top() + 10 && playerRect.top() < platRect.bottom() - 10) {
                collidingSidePlatform = true;
                player->setX(platRect.left() - playerRect.width());
                player->setVelocityX(0);
            }
            else if(player->getVelocityX() < 0 && playerRect.left() < platRect.right() && playerRect.right() > platRect.right() && playerRect.bottom() > platRect.top() + 10 && playerRect.top() < platRect.bottom() - 10) {
                collidingSidePlatform = true;
                player->setX(platRect.right());
                player->setVelocityX(0);
            }
            else if(player->getVelocityY() > 0 && playerRect.bottom() >= platRect.top() && playerRect.bottom() <= platRect.top() + 20 && playerRect.right() > platRect.left() + 5 && playerRect.left() < platRect.right() - 5) {
                player->setY(platRect.top() - playerRect.height() + 1);
                player->setVelocityY(0);
                player->setOnGround(true);
                landedOnPlatform = true;
            }
            else if(player->getVelocityY() < 0 && playerRect.top() < platRect.bottom() && playerRect.bottom() > platRect.bottom() && playerRect.right() > platRect.left() + 5 && playerRect.left() < platRect.right() - 5) {
                player->setY(platRect.bottom() + 1);
                player->setVelocityY(2);
            }
        }
        if(!collidingSidePlatform) {
            gameView->centerOn(player->pos());
        }
        if(!landedOnPlatform && !player->isOnGround()) {
            player->setOnGround(false);
        }
        for (auto enemy : enemies){
            enemy->move();
        }
        for(auto item : colliding){
            Coin* coin=dynamic_cast<Coin*>(item);
            if(coin){
                coinSound->play();
                gameScene->removeItem(item);
                delete item;
                score += 100;
                updateHUD();
            }
            if(dynamic_cast<Pole*>(item)&& !reachedPole){
                reachedPole=true;
                flag=new Flag();
                flag->setPos(5000-325,500);
                gameScene->addItem(flag);
                flag->setZValue(2);
            }        
            if(dynamic_cast<Castle*>(item)){
                if (!levelCompleted) {
                    levelCompleted = true;
                    gameScene->removeItem(player);
                    victorySong=new QSoundEffect(this);
                    victorySong->setSource(QUrl("qrc:/sounds/sounds/victory.wav"));
                    victorySong->setVolume(0.75);
                    themeSong->stop();
                    victorySong->play();
                    QTimer::singleShot(8000, this, [this]() {
                        LevelSelection *levelSelect = new LevelSelection();
                        levelSelect->show();
                        this->close();
                    });
                }
            }
            if(dynamic_cast<PowerUp*>(item)){
                applyPowerUp(((PowerUp*)item)->getType());
                powerupSound->play();
                gameScene->removeItem(item);
                delete item;
                score += 200;
                updateHUD();
            }
            Spiny* spiny=dynamic_cast<Spiny*>(item);
            Enemy* enemy=dynamic_cast<Enemy*>(item);
            if(spiny){
                if(!player->isInvincible()){
                    player->loseLife();
                    updateHUD();
                    if(player->getLives()<=0) {
                        gameScene->removeItem(player);
                        deathSong = new QSoundEffect(this);
                        deathSong->setSource(QUrl("qrc:/sounds/sounds/death.wav"));
                        deathSong->setVolume(0.25);
                        themeSong->stop();
                        deathSong->play();
                        QTimer::singleShot(8000, this, [this]() {
                            LevelSelection *levelSelect = new LevelSelection();
                            levelSelect->show();
                            this->close();
                        });
                    }
                }
            } else if(enemy){
                QRectF playerRect = player->sceneBoundingRect();
                QRectF enemyRect = enemy->sceneBoundingRect();
                if(player->getVelocityY()>0 && playerRect.bottom()<=enemyRect.top()+20&&playerRect.right()>enemyRect.left()+5 && playerRect.left()<enemyRect.right()-5){
                    if(!enemy->getIsSquished()) player->setVelocityY(-10);
                    enemy->squish();
                    score+=300;
                    updateHUD();
                }
                else if(!enemy->getIsSquished()){
                    if(!player->isInvincible()){
                        player->loseLife();
                        updateHUD();
                        if(player->getLives()<=0){
                            gameScene->removeItem(player);
                            deathSong = new QSoundEffect(this);
                            deathSong->setSource(QUrl("qrc:/sounds/sounds/death.wav"));
                            deathSong->setVolume(0.25);
                            themeSong->stop();
                            deathSong->play();
                            QTimer::singleShot(8000, this, [this]() {
                                LevelSelection *levelSelect = new LevelSelection();
                                levelSelect->show();
                                this->close();
                            });
                        }
                    }
                }
            }
        }
    }
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
