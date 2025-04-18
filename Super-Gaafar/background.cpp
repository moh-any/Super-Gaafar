#include "background.h"
#include <QPainter>
#include <QGraphicsScene>
Background::Background(){
    QPixmap tile(":/images/background.png");
    int tileW = tile.width();
    int tileH = tile.height();
    int repeatCount=10;
    QPixmap big(tileW *repeatCount, tileH);
    big.fill(Qt::transparent);
    QPainter p(&big);
    for(int i=0; i<repeatCount; ++i){
        p.drawPixmap(i*tileW,0,tile);
    }
    p.end();
    setPixmap(big);
    setPos(0,-100);
    setVisible(true);
}

