#ifndef LEVELSELECTION_H
#define LEVELSELECTION_H

#include <QMainWindow>
#include <QSoundEffect>
#include "credits.h"

namespace Ui {
class LevelSelection;
}

class LevelSelection : public QMainWindow
{
    Q_OBJECT

public:
    explicit LevelSelection(QWidget *parent = nullptr);
    ~LevelSelection();

private slots:
    void onLevel1ButtonClicked();
    void onLevel2ButtonClicked();
    void onLevel3ButtonClicked();
    void onLevel4ButtonClicked();
    void onLevel5ButtonClicked();
    void onCreditsButtonClicked();

private:
    Ui::LevelSelection *ui;
    QSoundEffect *menuSound;
    void startGame(int level);
};

#endif
