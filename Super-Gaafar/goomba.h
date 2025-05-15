#ifndef Goomba_H
#define Goomba_H

#include <enemy.h>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class Goomba : public Enemy {
    Q_OBJECT
public:
    Goomba(qreal x);
    void updateAnimation() override;
};

#endif // Goomba_H
