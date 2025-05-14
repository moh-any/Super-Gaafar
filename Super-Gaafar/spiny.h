#ifndef SPINY_H
#define SPINY_H

#include <enemy.h>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class Spiny : public Enemy {
    Q_OBJECT
public:
    Spiny(qreal x);
    void move() override;
private:
    void updateAnimation() override;
    void updateSprite() override;
};

#endif // SPINY_H
