#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include <QDialog>

namespace Ui {
class OrderManager;
}

class OrderManager : public QDialog
{
    Q_OBJECT

public:
    explicit OrderManager(QWidget *parent = nullptr);
    ~OrderManager();

private:
    Ui::OrderManager *ui;
};

#endif // ORDERMANAGER_H
