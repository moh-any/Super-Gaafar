#include "platform.h"
#include <Qstring>
#include <QPainter>
Platform::Platform(qreal x, qreal y, QString s, int length) {
    QString path = ":/images/";
    path.append(s);
    path.append(".png");
    QPixmap tile(path);
    int tileW = tile.width();
    int tileH = tile.height();
    QPixmap big(tileW *length, tileH);
    big.fill(Qt::transparent);
    QPainter p(&big);
    for(int i=0; i<length; ++i){
        p.drawPixmap(i*tileW,0,tile);
    }
    p.end();
    setPixmap(big);
    setPos(x,y);
}
