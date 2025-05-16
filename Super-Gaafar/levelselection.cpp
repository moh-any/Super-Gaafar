#include "levelselection.h"
#include "ui_levelselection.h"
#include "maingamewindow.h"
#include "credits.h"
#include <QFont>
#include <QSoundEffect>
#include <QUrl>
#include <QPushButton>

LevelSelection::LevelSelection(QWidget *parent) : QMainWindow(parent), ui(new Ui::LevelSelection)
{
    ui->setupUi(this);
    setWindowTitle("Super Gaafar - Level Selection");
    setFixedSize(800, 600);
    connect(ui->level1Button, &QPushButton::clicked, this, &LevelSelection::onLevel1ButtonClicked);
    connect(ui->level2Button, &QPushButton::clicked, this, &LevelSelection::onLevel2ButtonClicked);
    connect(ui->level3Button, &QPushButton::clicked, this, &LevelSelection::onLevel3ButtonClicked);
    connect(ui->level4Button, &QPushButton::clicked, this, &LevelSelection::onLevel4ButtonClicked);
    connect(ui->level5Button, &QPushButton::clicked, this, &LevelSelection::onLevel5ButtonClicked);
    connect(ui->creditsButton, &QPushButton::clicked, this, &LevelSelection::onCreditsButtonClicked);
    connect(ui->playGaafarsSong, &QPushButton::clicked, this, &LevelSelection::onPlayGaafarsSongClicked);
    ui->titleLabel->setFont(QFont("Arial", 32, QFont::Bold));
    ui->selectLevelLabel->setFont(QFont("Arial", 18));
    menuSound = new QSoundEffect(this);
    menuSound->setSource(QUrl("qrc:/sounds/sounds/ThemeSong.wav"));
    menuSound->setVolume(0.5);
    menuSound->setLoopCount(QSoundEffect::Infinite);
    menuSound->play();
}

LevelSelection::~LevelSelection()
{
    delete ui;
    if (menuSound) {
        menuSound->stop();
        delete menuSound;
    }
}

bool playedGaafarsSong = false;

void LevelSelection::startGame(int level)
{
    if (menuSound) {
        menuSound->stop();
    }
    MainGameWindow *gameWindow = new MainGameWindow(nullptr, level, playedGaafarsSong);
    gameWindow->show();
    this->close();
}

void LevelSelection::onLevel1ButtonClicked()
{
    startGame(1);
}

void LevelSelection::onLevel2ButtonClicked()
{
    startGame(2);
}

void LevelSelection::onLevel3ButtonClicked()
{
    startGame(3);
}

void LevelSelection::onLevel4ButtonClicked()
{
    startGame(4);
}

void LevelSelection::onLevel5ButtonClicked()
{
    startGame(5);
}

void LevelSelection::onCreditsButtonClicked()
{
    if (menuSound) {
        menuSound->stop();
    }
    Credits *creditsWindow = new Credits(this);
    creditsWindow->setAttribute(Qt::WA_DeleteOnClose);
    this->hide();
    creditsWindow->show();
}

void LevelSelection::onPlayGaafarsSongClicked()
{
    if (menuSound) {
        menuSound->stop();
        menuSound->setSource(QUrl("qrc:/sounds/sounds/friends.wav"));
        menuSound->setVolume(0.5);
        menuSound->setLoopCount(QSoundEffect::Infinite);
        menuSound->play();
    }
    playedGaafarsSong = true;
}
