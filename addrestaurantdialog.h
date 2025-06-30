#ifndef ADDRESTAURANTDIALOG_H
#define ADDRESTAURANTDIALOG_H

#include <QDialog>

namespace Ui {
class AddRestaurantDialog;
}

class AddRestaurantDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddRestaurantDialog(QWidget *parent = nullptr);
    ~AddRestaurantDialog();

private:
    Ui::AddRestaurantDialog *ui;
};

#endif // ADDRESTAURANTDIALOG_H
