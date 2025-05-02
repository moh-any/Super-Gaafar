#include "menu.h"
#include "ui_menu.h"
#include "maingamewindow.h"
#include "levelsmenu.h"

Menu::Menu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Menu)
{
    ui->setupUi(this);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_playButton_clicked()
{
    // MainGameWindow* gameWindow = new MainGameWindow();
    // gameWindow->show();
    LevelsMenu* levels = new LevelsMenu(this->parentWidget()); // or pass nullptr
    levels->show();
    this->close();
}

void Menu::on_quitButton_clicked()
{
    QApplication::quit();
}

