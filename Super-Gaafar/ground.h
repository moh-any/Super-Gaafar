#ifndef GROUND_H
#define GROUND_H

#include <QGraphicsPixmapItem>

class Ground :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Ground(QGraphicsItem *parent = nullptr);
private:
    QPixmap groundTexture;
};

#endif // GROUND_H
