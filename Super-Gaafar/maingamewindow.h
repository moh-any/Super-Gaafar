#ifndef MAINGAMEWINDOW_H
#define MAINGAMEWINDOW_H

#include <QMainWindow>
#include "player.h"
#include "platform.h"
#include "enemy.h"
#include <ground.h>
#include <background.h>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QEvent>
#include <QSoundEffect>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainGameWindow;
}
QT_END_NAMESPACE

class MainGameWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainGameWindow(QWidget *parent = nullptr);
    ~MainGameWindow();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    bool eventFilter(QObject *object,QEvent *event);

private slots:
    void updateGame();
    void setupGame();
    void spawnCoin();

private:
    Ui::MainGameWindow *ui;
    QGraphicsScene *gameScene;
    QGraphicsView *gameView;
    Player *player;
    Ground *ground;
    Background *bg;
    QList<Platform *> platforms;
    QList<Platform *> obstacles;
    QList<Enemy *> enemies;
    int PlatformsNum;
    int ObstaclesNum;
    int EnemiesNum;
    QTimer *gameTimer;
    QGraphicsTextItem* score;
    QSoundEffect* coinSound;

};
#endif // MAINGAMEWINDOW_H
