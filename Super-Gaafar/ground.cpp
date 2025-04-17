#include "ground.h"
#include <QGraphicsScene>

Ground::Ground():totalWidth(0),scrollOffset(0){
    groundTexture.load(":/images/ground.png");
    segmentWidth=groundTexture.width();
    createSegment(-100);
    setVisible(true);
}

QGraphicsPixmapItem* Ground::createSegment(double xPos){
    QGraphicsPixmapItem* segment=new QGraphicsPixmapItem(this);
    segment->setPixmap(groundTexture);
    segment->setPos(xPos, 0);
    groundSegments.append(segment);
    totalWidth+=segmentWidth;
    return segment;
}

void Ground::updateSegments(double viewWidth){
    double requiredWidth=viewWidth+segmentWidth*2;
    while(totalWidth<requiredWidth) {
        double xPos=-100;
        if(!groundSegments.isEmpty()) {
            QGraphicsPixmapItem* lastSegment=groundSegments.last();
            xPos=lastSegment->x()+segmentWidth;
        }
        createSegment(xPos);
    }
}

void Ground::scroll(double deltaX){
    scrollOffset += deltaX;
    for(auto segment:groundSegments){
        segment->setX(segment->x()-deltaX);
    }
    QGraphicsPixmapItem* firstSegment=groundSegments.first();
    if (firstSegment->x()+segmentWidth<-100) {
        double newX=groundSegments.last()->x()+segmentWidth;
        firstSegment->setX(newX);
        groundSegments.removeFirst();
        groundSegments.append(firstSegment);
    }
    QGraphicsPixmapItem* lastSegment=groundSegments.last();
    if(lastSegment->x()>scene()->width()+100){
        double newX=groundSegments.first()->x()-segmentWidth;
        lastSegment->setX(newX);
        groundSegments.removeLast();
        groundSegments.prepend(lastSegment);
    }
}
