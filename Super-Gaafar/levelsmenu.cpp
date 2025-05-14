#include "levelsmenu.h"
#include "ui_levelsmenu.h"
#include "menu.h"
#include "maingamewindow.h"

LevelsMenu::LevelsMenu(QWidget *parent)
    : QDialog(parent), ui(new Ui::LevelsMenu)
{
    ui->setupUi(this);
}

LevelsMenu::~LevelsMenu()
{
    delete ui;
}

void LevelsMenu::on_backButton_clicked()
{
    Menu *menu = new Menu(this->parentWidget()); // or pass nullptr
    menu->show();
    this->close();
}

// Level-1 button: open the game (which by default runs setupLevelOne())
void LevelsMenu::on_level1Button_clicked()
{
    MainGameWindow *game = new MainGameWindow(this->parentWidget(), 1);
    game->show();
    this->close();
}

void LevelsMenu::on_level2Button_clicked()
{
    MainGameWindow *game = new MainGameWindow(this->parentWidget(), 2);
    game->show();
    this->close();
}

void LevelsMenu::on_level3Button_clicked()
{
    MainGameWindow *game = new MainGameWindow(this->parentWidget(), 3);
    game->show();
    this->close();
}

void LevelsMenu::on_level4Button_clicked()
{
    MainGameWindow *game = new MainGameWindow(this->parentWidget(), 4);
    game->show();
    this->close();
}

void LevelsMenu::on_level5Button_clicked()
{
    MainGameWindow *game = new MainGameWindow(this->parentWidget(), 5);
    game->show();
    this->close();
}
