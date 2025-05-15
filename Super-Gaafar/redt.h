#ifndef REDT_H
#define REDT_H

#include <enemy.h>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class RedT : public Enemy {
    Q_OBJECT
public:
    RedT(qreal x);
    void updateAnimation() override;
};

#endif // REDT_H
