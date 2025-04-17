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
#include <QPoint>
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

    gameView=new QGraphicsView(gameScene,this);
    gameView->installEventFilter(this);
    gameView->setRenderHint(QPainter::Antialiasing);

    gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    statusBar()->setSizeGripEnabled(false);
    statusBar()->hide();
    setCentralWidget(gameView);

    player=new Player();
    gameScene->addItem(player);

    ground=new Ground();
    gameScene->addItem(ground);
    ground->setPos(-100, 600);
    ground->updateSegments(gameScene->width());

    bg=new Background();
    gameScene->addItem(bg);
    bg->setPos(-100,0);
    bg->updateSegments(gameScene->width());

    bg->setZValue(1);
    ground->setZValue(2);
    player->setZValue(3);
}

void MainGameWindow::scroll(){
    double scrollSpeed=0;
    if(player->pos().x()>gameView->width()*0.4){
        scrollSpeed=1.5;
        // player->setPos(player->pos().x()-scrollSpeed,player->pos().y());
        gameView->setSceneRect(cameraX,0,gameView->viewport()->width(),gameView->viewport()->height());
    }
    else if(player->pos().x()<gameView->width()*0.6){
        scrollSpeed=-1.5;
        // player->setPos(player->pos().x()-scrollSpeed,player->pos().y());
        gameView->setSceneRect(cameraX,0,gameView->viewport()->width(),gameView->viewport()->height());
    }
    // if(scrollSpeed!=0){
    //     bg->scroll(scrollSpeed);
    //     ground->scroll(scrollSpeed);
    // }
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
    updateCamera();
    scroll();
}

void MainGameWindow::updateCamera()
{
    int viewWidth=gameView->viewport()->width();

    double deadZoneLeft=cameraX+(viewWidth*0.35);
    double deadZoneRight=cameraX+(viewWidth*0.35);


    bool needsUpdate=false;
    double targetX = cameraX;
    if (player->x()<deadZoneLeft) {
        targetX = player->x() - (viewWidth * 0.35)+5;
        needsUpdate = true;
    }
    else if(player->x()>deadZoneRight) {
        targetX = player->x() - (viewWidth * 0.65);
        needsUpdate = true;
    }
    if (needsUpdate) {
        double smoothFactor = 1;
        double newCameraX = qMax(0.0,cameraX +(targetX-cameraX)*smoothFactor);

        double deltaX=newCameraX-cameraX;
        if (deltaX != 0) {
            cameraX = newCameraX;
            gameView->setSceneRect(cameraX, 0, viewWidth, gameView->viewport()->height());
        }
    }
}

