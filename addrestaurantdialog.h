#ifndef ADDRESTAURANTDIALOG_H
#define ADDRESTAURANTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

class AddRestaurantDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddRestaurantDialog(QWidget *parent = nullptr);

private slots:
    void onSubmit();

private:
    QLineEdit* nameEdit;
    QLineEdit* addressEdit;
    QPushButton* submitBtn;
    QPushButton* cancelBtn;
};

#endif // ADDRESTAURANTDIALOG_H
