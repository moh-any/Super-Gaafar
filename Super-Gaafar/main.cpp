#include "maingamewindow.h"
#include "menu.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // MainGameWindow w;
    // w.show();
    Menu w;
    w.show();

    return a.exec();
}
