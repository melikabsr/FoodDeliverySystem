#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <QDialog>

namespace Ui {
class Restaurant;
}

class Restaurant : public QDialog
{
    Q_OBJECT

public:
    explicit Restaurant(QWidget *parent = nullptr);
    ~Restaurant();

private:
    Ui::Restaurant *ui;
};

#endif // RESTAURANT_H
