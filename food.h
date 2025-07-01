#ifndef FOOD_H
#define FOOD_H

#include <QDialog>

namespace Ui {
class Food;
}

class Food : public QDialog
{
    Q_OBJECT

public:
    explicit Food(QWidget *parent = nullptr);
    ~Food();

private:
    Ui::Food *ui;
};

#endif // FOOD_H
