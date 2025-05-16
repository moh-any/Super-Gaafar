#include "credits.h"
#include "ui_credits.h"
#include <QGraphicsOpacityEffect>
#include <QSoundEffect>
#include "levelselection.h"

Credits::Credits(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Credits)
    , currentY(-600)
{
    ui->setupUi(this);
    setWindowTitle("Credits - Super Gaafar");
    
    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &Credits::updateAnimation);
    animationTimer->start(50);

    scrollAnimation = new QPropertyAnimation(ui->namesLabel, "geometry");
    scrollAnimation->setDuration(18000);
    scrollAnimation->setStartValue(QRect(0, -600, 800, 600));
    scrollAnimation->setEndValue(QRect(0, -30, 800, 600));
    scrollAnimation->start();

    QGraphicsOpacityEffect *fadeEffect = new QGraphicsOpacityEffect(this);
    ui->namesLabel->setGraphicsEffect(fadeEffect);
    fadeEffect->setOpacity(1.0);

    creditsMusic = new QSoundEffect(this);
    creditsMusic->setSource(QUrl("qrc:/sounds/sounds/credits.wav"));
    creditsMusic->setLoopCount(1);
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
    if (scrollAnimation->currentValue().toRect().y() >= 300) {
        scrollAnimation->stop();
        animationTimer->stop();
    }
}
