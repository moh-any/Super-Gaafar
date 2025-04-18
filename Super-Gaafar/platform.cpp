#include "platform.h"

Platform::Platform(qreal x, qreal y) {
    QPixmap original(":/images/brick.jpg");
    QPixmap scaled = original.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setPixmap(scaled);
    setPos(x,y);
}
