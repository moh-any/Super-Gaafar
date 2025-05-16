#include "credits.h"
#include "ui_credits.h"
#include <QGraphicsOpacityEffect>
#include <QSoundEffect>
#include "levelselection.h"

Credits::Credits(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Credits)
    , currentY(-600)  // Start from top of the window
{
    ui->setupUi(this);
    setWindowTitle("Credits - Super Gaafar");
    
    // Set up the animation timer
    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &Credits::updateAnimation);
    animationTimer->start(50);  // Update every 50ms for smooth animation

    // Set up the scroll animation
    scrollAnimation = new QPropertyAnimation(ui->namesLabel, "geometry");
    scrollAnimation->setDuration(18000);  // 20 seconds for full scroll
    scrollAnimation->setStartValue(QRect(0, -600, 800, 600));
    // Stop when the title is visible (around 300 pixels from top)
    scrollAnimation->setEndValue(QRect(0, -30, 800, 600));
    scrollAnimation->start();

    // Add a fade effect to the text
    QGraphicsOpacityEffect *fadeEffect = new QGraphicsOpacityEffect(this);
    ui->namesLabel->setGraphicsEffect(fadeEffect);
    fadeEffect->setOpacity(1.0);

    // Set up background music
    creditsMusic = new QSoundEffect(this);
    creditsMusic->setSource(QUrl("qrc:/sounds/sounds/credits.wav"));  // Make sure to add your music file to resources
    creditsMusic->setVolume(0.75);
    creditsMusic->setLoopCount(1);  // Play once
    creditsMusic->play();
}

Credits::~Credits()
{
    delete ui;
    if (creditsMusic) {
        creditsMusic->stop();
        delete creditsMusic;
    }
}

void Credits::on_backButton_clicked()
{
    if (creditsMusic) {
        creditsMusic->stop();
    }
    LevelSelection *menu = new LevelSelection();
    menu->show();
    this->close();
}

void Credits::updateAnimation()
{
    // Stop the animation and timer when it reaches the target position
    if (scrollAnimation->currentValue().toRect().y() >= 300) {
        scrollAnimation->stop();
        animationTimer->stop();
    }
}
