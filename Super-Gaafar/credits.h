#ifndef CREDITS_H
#define CREDITS_H

#include <QDialog>
#include <QPropertyAnimation>
#include <QTimer>
#include <QSoundEffect>

namespace Ui {
class Credits;
}

class Credits : public QDialog
{
    Q_OBJECT

public:
    explicit Credits(QWidget *parent = nullptr);
    ~Credits();

private slots:
    void on_backButton_clicked();
    void updateAnimation();

private:
    Ui::Credits *ui;
    QPropertyAnimation *scrollAnimation;
    QTimer *animationTimer;
    QSoundEffect *creditsMusic;
    int currentY;
};

#endif // CREDITS_H
