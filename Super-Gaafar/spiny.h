#ifndef SPINY_H
#define SPINY_H

#include <enemy.h>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class Spiny : public Enemy {
    Q_OBJECT
public:
    Spiny(qreal x);
    void updateAnimation() override;
};

#endif // SPINY_H
