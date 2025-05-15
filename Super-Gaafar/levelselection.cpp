#include "levelselection.h"
#include "ui_levelselection.h"
#include "maingamewindow.h"
#include <QFont>
#include <QSoundEffect>
#include <QUrl>
#include <QPushButton>

LevelSelection::LevelSelection(QWidget *parent) : QMainWindow(parent), ui(new Ui::LevelSelection)
{
    // Set up UI from the .ui file
    ui->setupUi(this);
    
    // Set window properties
    setWindowTitle("Super Gaafar - Level Selection");
    setFixedSize(800, 600);
    
    // Set up button connections
    connect(ui->level1Button, &QPushButton::clicked, this, &LevelSelection::onLevel1ButtonClicked);
    connect(ui->level2Button, &QPushButton::clicked, this, &LevelSelection::onLevel2ButtonClicked);
    connect(ui->level3Button, &QPushButton::clicked, this, &LevelSelection::onLevel3ButtonClicked);
    connect(ui->level4Button, &QPushButton::clicked, this, &LevelSelection::onLevel4ButtonClicked);
    connect(ui->level5Button, &QPushButton::clicked, this, &LevelSelection::onLevel5ButtonClicked);
    
    // Set font for labels
    ui->titleLabel->setFont(QFont("Arial", 32, QFont::Bold));
    ui->selectLevelLabel->setFont(QFont("Arial", 18));
    
    // Play menu sound
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

void LevelSelection::startGame(int level)
{
    // Stop menu music
    if (menuSound) {
        menuSound->stop();
    }
    
    // Create and show the main game window with the selected level
    MainGameWindow *gameWindow = new MainGameWindow(nullptr, level);
    gameWindow->show();
    
    // Close the level selection window
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
