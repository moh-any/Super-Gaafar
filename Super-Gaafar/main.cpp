#include "levelselection.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LevelSelection w;
    w.show();
    return a.exec();
}
