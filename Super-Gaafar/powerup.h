#ifndef POWERUP_H
#define POWERUP_H


#pragma once
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

enum PowerUpType { SpeedBoost, JumpBoost, Gigantification };

class PowerUp : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    PowerUp(PowerUpType type, QGraphicsItem* parent = nullptr);

    PowerUpType getType() const;

private:
    PowerUpType type;
};

#endif // POWERUP_H
