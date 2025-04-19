#include "powerup.h"
#include <QPixmap>

PowerUp::PowerUp(PowerUpType type, QGraphicsItem* parent)
    : QObject(), QGraphicsPixmapItem(parent), type(type)
{
    switch (type) {
    case SpeedBoost:
<<<<<<< HEAD
        setPixmap(QPixmap(":/images/SpeedUp.png").scaled(78, 78, Qt::KeepAspectRatio, Qt::SmoothTransformation));
=======
        setPixmap(QPixmap(":/images/speedBoost.png").scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));
>>>>>>> efe10f60e5238827d4b4fada4d846132ba7b4703
        break;
    case JumpBoost:
        setPixmap(QPixmap(":/images/JumpUp.png").scaled(48, 48, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        break;
    case Gigantification:
        setPixmap(QPixmap(":/images/GiantUp.png").scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        break;
    }
<<<<<<< HEAD
    setScale(0.8); // Adjust size
=======
    setScale(0.8);
>>>>>>> efe10f60e5238827d4b4fada4d846132ba7b4703
}

PowerUpType PowerUp::getType() const {
    return type;
}
