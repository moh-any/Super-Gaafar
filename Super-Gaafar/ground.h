#ifndef GROUND_H
#define GROUND_H

#include <QGraphicsPixmapItem>
#include <QVector>

class Ground : public QGraphicsPixmapItem
{
public:
    Ground();
    void scroll(double deltaX);
    void updateSegments(double viewWidth);
private:
    QPixmap groundTexture;
    QVector<QGraphicsPixmapItem*> groundSegments;
    double totalWidth;
    double segmentWidth;
    double scrollOffset;
    QGraphicsPixmapItem* createSegment(double xPos);
};

#endif // GROUND_H
