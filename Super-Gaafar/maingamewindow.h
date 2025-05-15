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
    MainGameWindow(QWidget *parent = nullptr);
    ~MainGameWindow();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    bool eventFilter(QObject *object,QEvent *event);

private slots:
    void updateGame();
    void setupGame();
    void applyPowerUp(PowerUpType type);
    // Level setup functions
    void level1Setup();
    void level2Setup();
    void level3Setup();
    void level4Setup();
    void level5Setup();

private:
    Ui::MainGameWindow *ui;
    QGraphicsScene *gameScene;
    QGraphicsView *gameView;
    QGraphicsScene *hudScene;  // Scene for HUD elements
    QGraphicsView *hudView;    // View for HUD elements
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
    QList<Platform *> platforms;
    QList<Platform *> obstacles;
    QList<Enemy *> enemies;
    QList<QGraphicsItem *> levelItems; // To track level-specific items for cleanup
    int PlatformsNum;
    int ObstaclesNum;
    int EnemiesNum;
    int score = 0;
    int currentLevel = 1; // Track the current level
    QGraphicsTextItem* scoreText = nullptr;
    QGraphicsTextItem* livesText = nullptr;
    QGraphicsTextItem* levelText = nullptr; // Display current level
    void updateHUD();
    void changeLevel(int newLevel); // Method to change levels
    void clearCurrentLevel(); // Method to clear current level items
};
#endif // MAINGAMEWINDOW_H
