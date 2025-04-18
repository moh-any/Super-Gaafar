#ifndef FLAG_H
#define FLAG_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Flag : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Flag(QGraphicsItem *parent = nullptr);

private slots:
    void nextFrame();
private:
    QPixmap flag;
    int frameCount;
    int frameWidth;
    int frameHeight;
    int currentFrame=0;
    QTimer *animationTimer;
};

#endif // FLAG_H
