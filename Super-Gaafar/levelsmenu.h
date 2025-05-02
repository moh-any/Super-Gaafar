#ifndef LEVELSMENU_H
#define LEVELSMENU_H

#include <QDialog>

namespace Ui {
class LevelsMenu;
}

class LevelsMenu : public QDialog
{
    Q_OBJECT

public:
    explicit LevelsMenu(QWidget *parent = nullptr);
    ~LevelsMenu();

private slots:
    void on_level1Button_clicked();
    void on_level2Button_clicked();
    void on_level3Button_clicked();
    void on_level4Button_clicked();
    void on_level5Button_clicked();

    void on_backButton_clicked();



private:
    Ui::LevelsMenu *ui;
};

#endif // LEVELSMENU_H
