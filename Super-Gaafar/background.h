#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <QGraphicsPixmapItem>
#include <QVector>
class Background: public QGraphicsPixmapItem
{
public:
    Background();
    void scroll(double deltaX);
    void updateSegments(double viewWidth);
private:
    QPixmap bgTexture;
    QVector<QGraphicsPixmapItem*> bgSegments;
    double totalWidth;
    double segmentWidth;
    double scrollOffset;
    QGraphicsPixmapItem* createSegment(double xPos);
};

#endif // BACKGROUND_H
