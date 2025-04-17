#include "background.h"
#include <QGraphicsScene>
Background::Background():totalWidth(0),scrollOffset(0){
    bgTexture.load(":/images/background.png");
    segmentWidth=bgTexture.width();
    createSegment(-100);
    setVisible(true);
}

QGraphicsPixmapItem* Background::createSegment(double xPos){
    QGraphicsPixmapItem* segment=new QGraphicsPixmapItem(this);
    segment->setPixmap(bgTexture);
    segment->setPos(xPos, 0);
    bgSegments.append(segment);
    totalWidth+=segmentWidth;
    return segment;
}

void Background::updateSegments(double viewWidth){
    double requiredWidth=viewWidth+segmentWidth*2;
    while(totalWidth<requiredWidth) {
        double xPos=-100;
        if(!bgSegments.isEmpty()) {
            QGraphicsPixmapItem* lastSegment=bgSegments.last();
            xPos=lastSegment->x()+segmentWidth;
        }
        createSegment(xPos);
    }
}

void Background::scroll(double deltaX){
    scrollOffset += deltaX;
    for(auto segment:bgSegments){
        segment->setX(segment->x()-deltaX);
    }
    QGraphicsPixmapItem* firstSegment=bgSegments.first();
    if (firstSegment->x()+segmentWidth<-100) {
        double newX=bgSegments.last()->x()+segmentWidth;
        firstSegment->setX(newX);
        bgSegments.removeFirst();
        bgSegments.append(firstSegment);
    }
    QGraphicsPixmapItem* lastSegment=bgSegments.last();
    if(lastSegment->x()>scene()->width()+100){
        double newX=bgSegments.first()->x()-segmentWidth;
        lastSegment->setX(newX);
        bgSegments.removeLast();
        bgSegments.prepend(lastSegment);
    }
}
