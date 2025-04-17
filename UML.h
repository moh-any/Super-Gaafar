#ifndef SUPERGAAFAR_H
#define SUPERGAAFAR_H

#include <QObject>
#include <QString>
#include <QPointF>
#include <QVector>

// ==============================
// Game Class (1)
// ==============================
class Game : public QObject {
    Q_OBJECT
public:
    Game(QObject *parent = nullptr);
    ~Game();
    void start();
    void stop();
    void setnextLevel();
    void updateScore(int points);

private:
    int score;
    int currentLevel;
    int lives;
};

// ==============================
// Player Class (2)
// ==============================
class Player : public QObject {
    Q_OBJECT
public:
    Player(QObject *parent = nullptr);
    ~Player();

    // Setters and getters for position and health
    void setPosition(const QPointF &pos);
    QPointF position() const;

    void setHealth(int health);
    int health() const;
    // Movement actions
    void moveForward();
    void moveBackward();
    void jump();
    void playerMoved(const QPointF &newPos);
    void healthChanged(int newHealth);

private:
    QPointF position;
    int health;
};

// ==============================
// Level Class (3)
// ==============================
class Level : public QObject {
    Q_OBJECT
public:
    Level(int levelNumber, QObject *parent = nullptr);
    ~Level();

    void loadLevel();
    void clearLevel();
    int levelNumber() const;

private:
    int levelNumber;
    string backgroundimage;
    string backgroundsound;
    // You might store obstacles and enemies here
    QVector<class Obstacle*> obstacles;
    QVector<class Enemy*> enemies;
};

// ==============================
// Obstacle Class (4)
// ==============================

class Obstacle : public QObject {
    Q_OBJECT
public:
    Obstacle(QObject *parent = nullptr);
    virtual ~Obstacle();

    void setPosition(const QPointF &pos);
    QPointF position() const;

    // Virtual function to handle collision with the player
    virtual void onCollision(Player *player);

protected:
    QPointF position;
};

// ==============================
// MovingObstacle Class (5)
// ==============================
class MovingObstacle : public Obstacle {
    Q_OBJECT
public:
    MovingObstacle(QObject *parent = nullptr);
    ~MovingObstacle();

    // Overrides the onCollision function if needed
    void onCollision(Player *player) override;

    void setVelocity(const QPointF &velocity);
    QPointF velocity() const;

    // Function to update the position over time
    void updatePosition();

private:
    QPointF velocity;
};

// ==============================
// Enemy Class (6)
// ==============================
class Enemy : public QObject {
    Q_OBJECT
public:
    Enemy(QObject *parent = nullptr);
    ~Enemy();

    void setPosition(const QPointF &pos);
    QPointF position() const;

    // Function to simulate enemy behavior (e.g., patrol)
    virtual void attack();

    // Interact with the player
    virtual void onCollision(Player *player);

protected:
    QPointF position;
};

// ==============================
// PowerUp Class (7 - Modified Item)
// ==============================
class PowerUp : public QObject {
    Q_OBJECT
public:
    PowerUp(QObject *parent = nullptr);
    ~PowerUp();

    void setPosition(const QPointF &pos);
    QPointF position() const;

    // Activate the power-up effect on the player
    void activate(Player *player);

    // Type/name of the power-up
    QString type() const;
    void setType(const QString &type);

private:
    QPointF position;
    QString type; // E.g., "Extra Life", "Speed Boost", etc.
    Qstring duration;
};

// ==============================
// MainMenu Class (15)
// ==============================
class MainMenu : public QObject {
    Q_OBJECT
public:
    MainMenu(QObject *parent = nullptr);
    ~MainMenu();

    void display();      // Display the main menu
    void selectOption(const QString &option);

signals:
    void startGame();
    void exitGame();
    void pause();

private:
    // Menu options can be stored here
    QVector<QString> options;
};

#endif // SUPERGAAFAR_H