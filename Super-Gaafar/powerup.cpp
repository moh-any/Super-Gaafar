#include "powerup.h"
#include <QPixmap>

PowerUp::PowerUp(PowerUpType type, QGraphicsItem* parent)
    : QObject(), QGraphicsPixmapItem(parent), type(type)
{
    switch (type) {
    case SpeedBoost:
        setPixmap(QPixmap(":/images/speedBoost.png").scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        break;
    case JumpBoost:
        setPixmap(QPixmap(":/images/JumpUp.png").scaled(48, 48, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        break;
    case Gigantification:
        setPixmap(QPixmap(":/images/GiantUp.png").scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        break;
    }
    setScale(0.8);
}

PowerUpType PowerUp::getType() const {
    return type;
}
