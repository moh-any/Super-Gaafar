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

    // Setup the current level based on parameter
    currentLevel = startLevel;
    
    // Initialize the appropriate level
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
            level1Setup(); // Fallback to level 1
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

    // HUD setup - added to UI layer, not the scene
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
    
    // Create a separate scene for HUD that stays fixed
    hudScene = new QGraphicsScene(this);
    hudScene->addItem(scoreText);
    hudScene->addItem(livesText);
    hudScene->addItem(levelText);
    
    // Create a view for the HUD and overlay it on main view
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
    // Platforms setup
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

    // Obstacles setup
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

    // Enemies setup
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

    // Coins setup
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

    // End level items
    Pole* pole = new Pole();
    pole->setPos(5000-350, 365);
    gameScene->addItem(pole);
    pole->setZValue(2);

    Castle* castle = new Castle();
    castle->setPos(5000-230, 370);
    gameScene->addItem(castle);
    castle->setZValue(2);

    // Power-ups setup
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
    // Platforms setup (more and spaced further apart than level 1)
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

    // Obstacles setup (more and some on platforms)
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

    // Enemies setup (more, and some on platforms)
    RedT *e1 = new RedT(1000); // on ground
    RedT *e2 = new RedT(1600); // on ground
    Spiny *e3 = new Spiny(2200); // on ground
    Goomba *e4 = new Goomba(2800); // on ground
    Spiny *e5 = new Spiny(3500); // on ground
    Goomba *e6 = new Goomba(4100); // on ground
    RedT *e7 = new RedT(4700); // on ground
    // Enemies on platforms
    Goomba *e8 = new Goomba(950); // on p2
    Spiny *e9 = new Spiny(2120); // on p4

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

    // Coins setup (optional, for reward)
    Coin* coin1 = new Coin(); coin1->setPos(450, 300); gameScene->addItem(coin1); coin1->setZValue(3);
    Coin* coin2 = new Coin(); coin2->setPos(950, 250); gameScene->addItem(coin2); coin2->setZValue(3);
    Coin* coin3 = new Coin(); coin3->setPos(1550, 350); gameScene->addItem(coin3); coin3->setZValue(3);
    Coin* coin4 = new Coin(); coin4->setPos(2150, 270); gameScene->addItem(coin4); coin4->setZValue(3);
    Coin* coin5 = new Coin(); coin5->setPos(2750, 320); gameScene->addItem(coin5); coin5->setZValue(3);
    Coin* coin6 = new Coin(); coin6->setPos(3450, 370); gameScene->addItem(coin6); coin6->setZValue(3);
    Coin* coin7 = new Coin(); coin7->setPos(4050, 300); gameScene->addItem(coin7); coin7->setZValue(3);
    Coin* coin8 = new Coin(); coin8->setPos(4650, 250); gameScene->addItem(coin8); coin8->setZValue(3);

    // End level items
    Pole* pole = new Pole();
    pole->setPos(5000-350, 365);
    gameScene->addItem(pole);
    pole->setZValue(2);

    Castle* castle = new Castle();
    castle->setPos(5000-230, 370);
    gameScene->addItem(castle);
    castle->setZValue(2);

    // Power-ups setup
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
    // --- Platforms: varied heights and spacing ---
    auto *p1 = new Platform(350, 420, "brick", 3);    // start
    auto *p2 = new Platform(900, 350, "brick", 4);    // mid-high
    auto *p3 = new Platform(1550, 350, "brick", 3);   // ground
    auto *p4 = new Platform(2100, 320, "brick", 2);   // high
    auto *p5 = new Platform(2650, 400, "brick", 3);   // mid
    auto *p6 = new Platform(3300, 350, "brick", 2);  // high

    gameScene->addItem(p1); p1->setZValue(3);
    gameScene->addItem(p2); p2->setZValue(3);
    gameScene->addItem(p3); p3->setZValue(3);
    gameScene->addItem(p4); p4->setZValue(3);
    gameScene->addItem(p5); p5->setZValue(3);
    gameScene->addItem(p6); p6->setZValue(3);

    // --- Obstacles: spaced between platforms, not overlapping ---
    auto *o1 = new Platform(700, 465, "warp");  // after p2
    auto *o3 = new Platform(1800, 465, "warp");  // after p3
    auto *o4 = new Platform(2500, 465, "warp");  // after p4
    auto *o5 = new Platform(3100, 465, "warp");  // after p5
    auto *o6 = new Platform(3700, 465, "warp");  // after p6
    auto *o7 = new Platform(4200, 465, "warp");  // after p7
    gameScene->addItem(o1); o1->setZValue(3);
    gameScene->addItem(o3); o3->setZValue(3);
    gameScene->addItem(o4); o4->setZValue(3);
    gameScene->addItem(o5); o5->setZValue(3);
    gameScene->addItem(o6); o6->setZValue(3);
    gameScene->addItem(o7); o7->setZValue(3);

    // --- Enemies: never stacked, spaced, some on platforms, some on ground ---
    Goomba *e1 = new Goomba(600);    // ground, before o1
    Spiny  *e2 = new Spiny(1150);    // ground, after o1
    RedT   *e3 = new RedT(1700);     // ground, after o2
    Goomba *e4 = new Goomba(2250);   // ground, after o3
    Spiny  *e5 = new Spiny(2950);    // ground, after o4
    RedT   *e6 = new RedT(3550);     // ground, after o5
    Goomba *e7 = new Goomba(4150);   // ground, after o6
    // Enemies on platforms (centered, not stacked)
    Spiny  *e8 = new Spiny(950);     // on p2
    RedT   *e9 = new RedT(2100);     // on p4
    Goomba *e10 = new Goomba(2650);  // on p5
    Spiny  *e11 = new Spiny(3900);   // on p7
    RedT   *e12 = new RedT(4450);    // on p8
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

    // --- Coins: on/above platforms and in gaps ---
    Coin* coin1 = new Coin(); coin1->setPos(400, 370); gameScene->addItem(coin1); coin1->setZValue(3);
    Coin* coin2 = new Coin(); coin2->setPos(950, 300); gameScene->addItem(coin2); coin2->setZValue(3);
    Coin* coin3 = new Coin(); coin3->setPos(1550, 370); gameScene->addItem(coin3); coin3->setZValue(3);
    Coin* coin4 = new Coin(); coin4->setPos(2100, 270); gameScene->addItem(coin4); coin4->setZValue(3);
    Coin* coin5 = new Coin(); coin5->setPos(2650, 350); gameScene->addItem(coin5); coin5->setZValue(3);
    Coin* coin6 = new Coin(); coin6->setPos(3300, 300); gameScene->addItem(coin6); coin6->setZValue(3);
    Coin* coin7 = new Coin(); coin7->setPos(3900, 370); gameScene->addItem(coin7); coin7->setZValue(3);
    Coin* coin8 = new Coin(); coin8->setPos(4450, 270); gameScene->addItem(coin8); coin8->setZValue(3);

    // --- End level items ---
    Pole* pole = new Pole();
    pole->setPos(5000-350, 365);
    gameScene->addItem(pole);
    pole->setZValue(2);
    Castle* castle = new Castle();
    castle->setPos(5000-230, 370);
    gameScene->addItem(castle);
    castle->setZValue(2);

    // --- Power-ups: accessible, not overlapping ---
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
    // Level 4: Hard - more platforms, more verticality, more enemies
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

    // Obstacles
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

    // Enemies (ground and platforms, spaced)
    Goomba *e1 = new Goomba(500);    // ground
    Spiny  *e2 = new Spiny(1000);    // ground
    RedT   *e3 = new RedT(1700);     // ground
    Goomba *e4 = new Goomba(2300);   // ground
    Spiny  *e5 = new Spiny(2800);    // ground
    RedT   *e6 = new RedT(3500);     // ground
    Goomba *e7 = new Goomba(4100);   // ground
    Spiny  *e8 = new Spiny(4700);    // ground
    // On platforms
    RedT   *e9 = new RedT(800);      // p2
    Goomba *e10 = new Goomba(1900);  // p4
    Spiny  *e11 = new Spiny(3150);   // p6
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
    // Coins
    Coin* coin1 = new Coin(); coin1->setPos(350, 370); gameScene->addItem(coin1); coin1->setZValue(3);
    Coin* coin2 = new Coin(); coin2->setPos(800, 300); gameScene->addItem(coin2); coin2->setZValue(3);
    Coin* coin3 = new Coin(); coin3->setPos(1400, 250); gameScene->addItem(coin3); coin3->setZValue(3);
    Coin* coin4 = new Coin(); coin4->setPos(1900, 350); gameScene->addItem(coin4); coin4->setZValue(3);
    Coin* coin5 = new Coin(); coin5->setPos(2500, 270); gameScene->addItem(coin5); coin5->setZValue(3);
    Coin* coin6 = new Coin(); coin6->setPos(3100, 320); gameScene->addItem(coin6); coin6->setZValue(3);
    Coin* coin7 = new Coin(); coin7->setPos(3700, 250); gameScene->addItem(coin7); coin7->setZValue(3);
    Coin* coin8 = new Coin(); coin8->setPos(4200, 370); gameScene->addItem(coin8); coin8->setZValue(3);
    Coin* coin9 = new Coin(); coin9->setPos(4700, 300); gameScene->addItem(coin9); coin9->setZValue(3);

    // End level items
    Pole* pole = new Pole();
    pole->setPos(5000-350, 365);
    gameScene->addItem(pole);
    pole->setZValue(2);
    Castle* castle = new Castle();
    castle->setPos(5000-230, 370);
    gameScene->addItem(castle);
    castle->setZValue(2);

    // Power-ups
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
    // Level 5: Expert - refined for maximum challenge and variety
    // Platforms (vertical, horizontal, some small, some far apart)
    auto *p1 = new Platform(200, 420, "brick", 2);      // start
    auto *p2 = new Platform(600, 350, "brick", 2);      // small, mid
    auto *p3 = new Platform(950, 270, "brick", 1);      // high, small
    auto *p4 = new Platform(1350, 400, "brick", 3);     // wide
    auto *p5 = new Platform(1800, 320, "brick", 2);     // mid-high
    auto *p6 = new Platform(2200, 250, "brick", 1);     // high, small
    auto *p7 = new Platform(2600, 370, "brick", 2);     // mid
    auto *p8 = new Platform(3050, 300, "brick", 2);     // high
    auto *p9 = new Platform(3500, 220, "brick", 1);     // very high
    auto *p10 = new Platform(3900, 350, "brick", 2);    // mid
    auto *p11 = new Platform(4300, 270, "brick", 1);    // high
    auto *p12 = new Platform(4700, 420, "brick", 2);    // end, ground
    gameScene->addItem(p1); p1->setZValue(3);
    gameScene->addItem(p2); p2->setZValue(3);
    gameScene->addItem(p3); p3->setZValue(3);
    gameScene->addItem(p4); p4->setZValue(3);
    gameScene->addItem(p5); p5->setZValue(3);
    gameScene->addItem(p6); p6->setZValue(3);
    gameScene->addItem(p7); p7->setZValue(3);
    gameScene->addItem(p8); p8->setZValue(3);
    gameScene->addItem(p9); p9->setZValue(3);
    gameScene->addItem(p10); p10->setZValue(3);
    gameScene->addItem(p11); p11->setZValue(3);
    gameScene->addItem(p12); p12->setZValue(3);

    // Obstacles (lots, spaced, some after jumps, no overlap)
    auto *o1 = new Platform(400, 465, "warp");
    auto *o2 = new Platform(800, 465, "warp");
    auto *o3 = new Platform(1200, 465, "warp");
    auto *o4 = new Platform(1600, 465, "warp");
    auto *o5 = new Platform(2000, 465, "warp");
    auto *o6 = new Platform(2400, 465, "warp");
    auto *o7 = new Platform(2800, 465, "warp");
    auto *o8 = new Platform(3200, 465, "warp");
    auto *o9 = new Platform(3600, 465, "warp");
    auto *o10 = new Platform(4000, 465, "warp");
    auto *o11 = new Platform(4400, 465, "warp");
    gameScene->addItem(o1); o1->setZValue(3);
    gameScene->addItem(o2); o2->setZValue(3);
    gameScene->addItem(o3); o3->setZValue(3);
    gameScene->addItem(o4); o4->setZValue(3);
    gameScene->addItem(o5); o5->setZValue(3);
    gameScene->addItem(o6); o6->setZValue(3);
    gameScene->addItem(o7); o7->setZValue(3);
    gameScene->addItem(o8); o8->setZValue(3);
    gameScene->addItem(o9); o9->setZValue(3);
    gameScene->addItem(o10); o10->setZValue(3);
    gameScene->addItem(o11); o11->setZValue(3);

    // Enemies (ground and platforms, spaced, no stacking)
    Goomba *e1 = new Goomba(350);    // ground
    Spiny  *e2 = new Spiny(850);     // ground
    RedT   *e3 = new RedT(1300);     // ground
    Goomba *e4 = new Goomba(1750);   // ground
    Spiny  *e5 = new Spiny(2200);    // ground
    RedT   *e6 = new RedT(2650);     // ground
    Goomba *e7 = new Goomba(3100);   // ground
    Spiny  *e8 = new Spiny(3550);    // ground
    RedT   *e9 = new RedT(4000);     // ground
    Goomba *e10 = new Goomba(4450);  // ground
    // On platforms (centered, not stacked)
    Spiny  *e11 = new Spiny(600);    // p2
    RedT   *e12 = new RedT(1350);    // p4
    Goomba *e13 = new Goomba(1800);  // p5
    Spiny  *e14 = new Spiny(2600);   // p7
    RedT   *e15 = new RedT(3500);    // p9
    Goomba *e16 = new Goomba(4700);  // p12
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
    enemies.append(e13); gameScene->addItem(e13); e13->setZValue(3);
    enemies.append(e14); gameScene->addItem(e14); e14->setZValue(3);
    enemies.append(e15); gameScene->addItem(e15); e15->setZValue(3);
    enemies.append(e16); gameScene->addItem(e16); e16->setZValue(3);

    // Coins (hard to reach, but fair)
    Coin* coin1 = new Coin(); coin1->setPos(200, 370); gameScene->addItem(coin1); coin1->setZValue(3);
    Coin* coin2 = new Coin(); coin2->setPos(600, 300); gameScene->addItem(coin2); coin2->setZValue(3);
    Coin* coin3 = new Coin(); coin3->setPos(950, 220); gameScene->addItem(coin3); coin3->setZValue(3);
    Coin* coin4 = new Coin(); coin4->setPos(1350, 350); gameScene->addItem(coin4); coin4->setZValue(3);
    Coin* coin5 = new Coin(); coin5->setPos(1800, 270); gameScene->addItem(coin5); coin5->setZValue(3);
    Coin* coin6 = new Coin(); coin6->setPos(2200, 200); gameScene->addItem(coin6); coin6->setZValue(3);
    Coin* coin7 = new Coin(); coin7->setPos(2600, 320); gameScene->addItem(coin7); coin7->setZValue(3);
    Coin* coin8 = new Coin(); coin8->setPos(3050, 250); gameScene->addItem(coin8); coin8->setZValue(3);
    Coin* coin9 = new Coin(); coin9->setPos(3500, 170); gameScene->addItem(coin9); coin9->setZValue(3);
    Coin* coin10 = new Coin(); coin10->setPos(3900, 300); gameScene->addItem(coin10); coin10->setZValue(3);
    Coin* coin11 = new Coin(); coin11->setPos(4300, 220); gameScene->addItem(coin11); coin11->setZValue(3);
    Coin* coin12 = new Coin(); coin12->setPos(4700, 370); gameScene->addItem(coin12); coin12->setZValue(3);

    // End level items
    Pole* pole = new Pole();
    pole->setPos(5000-350, 365);
    gameScene->addItem(pole);
    pole->setZValue(2);
    Castle* castle = new Castle();
    castle->setPos(5000-230, 370);
    gameScene->addItem(castle);
    castle->setZValue(2);

    // Power-ups (hard to reach)
    PowerUp* powerup1 = new PowerUp(Gigantification);
    powerup1->setPos(1350, 520);
    powerup1->setZValue(3);
    gameScene->addItem(powerup1);
    PowerUp* powerup2 = new PowerUp(SpeedBoost);
    powerup2->setPos(2600, 520);
    powerup2->setZValue(3);
    gameScene->addItem(powerup2);
    PowerUp* powerup3 = new PowerUp(JumpBoost);
    powerup3->setPos(3900, 520);
    powerup3->setZValue(3);
    gameScene->addItem(powerup3);
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
                    // Reopen the level selection menu after victory
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
                        // Return to level selection after death
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
