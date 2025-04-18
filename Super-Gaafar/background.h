#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <QGraphicsPixmapItem>
#include <QVector>
class Background: public QGraphicsPixmapItem
{
public:
    Background();
private:
    QPixmap bgTexture;
};

#endif // BACKGROUND_H
