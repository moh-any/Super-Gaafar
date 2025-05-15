#include "maingamewindow.h"
#include "levelselection.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // Create and show the level selection screen instead of the game window
    LevelSelection levelSelect;
    levelSelect.show();

    return a.exec();
}
