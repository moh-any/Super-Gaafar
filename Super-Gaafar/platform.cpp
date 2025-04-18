#include "platform.h"
#include <Qstring>

Platform::Platform(qreal x, qreal y, QString s) {
    //QPixmap original(":/images/brick.png");
    //QPixmap scaled = original.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QString path = ":/images/";
    path.append(s);
    path.append(".png");
    setPixmap(QPixmap(path));
    setPos(x,y);
}
