#ifndef MENU_H
#define MENU_H

#include <QDialog>

namespace Ui {
class Menu;
}

class Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

private slots:
    void on_playButton_clicked();

    void on_quitButton_clicked();

    void on_creditsButton_clicked();

private:
    Ui::Menu *ui;
};

#endif // MENU_H
