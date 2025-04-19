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
<<<<<<< HEAD
#include "coin.h"
#include "powerup.h"
=======
#include <powerup.h>
#include <platform.h>
#include <enemy.h>
>>>>>>> efe10f60e5238827d4b4fada4d846132ba7b4703

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
    void spawnPowerUp();
    void applyPowerUp(PowerUpType type);

private slots:
    void updateGame();
    void setupGame();
    void spawnCoin();
    void applyPowerUp(PowerUpType type);

private:
    Ui::MainGameWindow *ui;
    QGraphicsScene *gameScene;
    QGraphicsView *gameView;
    Player *player;
    Ground *ground;
    Background *bg;
    QTimer *gameTimer;
    QGraphicsTextItem* score;
    QSoundEffect* coinSound;
<<<<<<< HEAD
    QTimer* powerupTimer;


=======
    QSoundEffect* themeSong;
    QSoundEffect* victorySong;
    QSoundEffect* deathSong;
    Flag *flag;
    bool reachedPole=false;
    QList<Platform *> platforms;
    QList<Platform *> obstacles;
    QList<Enemy *> enemies;
    int PlatformsNum;
    int ObstaclesNum;
    int EnemiesNum;
>>>>>>> efe10f60e5238827d4b4fada4d846132ba7b4703
};
#endif // MAINGAMEWINDOW_H
