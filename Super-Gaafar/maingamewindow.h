#ifndef MAINGAMEWINDOW_H
#define MAINGAMEWINDOW_H

#include <QMainWindow>
#include "player.h"
#include <ground.h>
#include <background.h>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QEvent>
#include <flag.h>
#include <QSoundEffect>
#include <powerup.h>
#include <platform.h>
#include <enemy.h>
#include <QGraphicsTextItem>
#include <QPixmap>
#include <coin.h>
#include <pole.h>
#include <castle.h>
#include <redt.h>
#include <spiny.h>
#include <goomba.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainGameWindow;
}
QT_END_NAMESPACE

class MainGameWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainGameWindow(QWidget *parent = nullptr, int startLevel = 1);
    MainGameWindow(QWidget *parent = nullptr, int startLevel = 1, bool playGaafarsSong = false);
    ~MainGameWindow();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    bool eventFilter(QObject *object,QEvent *event);

public slots:
    void playGaafarsSong();

private slots:
    void updateGame();
    void setupGame(int startLevel = 1);
    void applyPowerUp(PowerUpType type);
    void level1Setup();
    void level2Setup();
    void level3Setup();
    void level4Setup();
    void level5Setup();

private:
    Ui::MainGameWindow *ui;
    QGraphicsScene *gameScene;
    QGraphicsView *gameView;
    QGraphicsScene *hudScene;
    QGraphicsView *hudView;
    Player *player;
    Ground *ground;
    Background *bg;
    QTimer *gameTimer;
    QSoundEffect* coinSound;
    QSoundEffect* themeSong;
    QSoundEffect* victorySong;
    QSoundEffect* deathSong;
    QSoundEffect* powerupSound;
    QSoundEffect* levelCompletedSound;
    Flag *flag;
    bool reachedPole=false;
    bool levelCompleted = false;
    QList<Platform *> platforms;
    QList<Platform *> obstacles;
    QList<Enemy *> enemies;
    QList<QGraphicsItem *> levelItems;
    int PlatformsNum;
    int ObstaclesNum;
    int EnemiesNum;
    int score = 0;
    int currentLevel = 1;
    QGraphicsTextItem* scoreText = nullptr;
    QGraphicsTextItem* livesText = nullptr;
    QGraphicsTextItem* levelText = nullptr;
    void updateHUD();
    void changeLevel(int newLevel);
    void clearCurrentLevel();
};
#endif // MAINGAMEWINDOW_H
