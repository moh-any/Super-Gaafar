#include "platform.h"

Platform::Platform(qreal x, qreal y) {
    //QPixmap original(":/images/brick.png");
    //QPixmap scaled = original.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setPixmap(QPixmap(":/images/brick.png"));
    setPos(x,y);
}
