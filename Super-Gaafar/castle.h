#ifndef CASTLE_H
#define CASTLE_H

#include <QObject>
#include <QGraphicsPixmapItem>


class Castle : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Castle(QGraphicsItem *parent = nullptr);
private:
    QPixmap castle;
};

#endif
