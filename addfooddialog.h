#ifndef ADD_FOOD_DIALOG_H
#define ADD_FOOD_DIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "Food.h"

class AddFoodDialog : public QDialog
{
    Q_OBJECT

public:
     //explicit AddFoodDialog(Restaurant& restRef, QWidget* parent = nullptr);
    explicit AddFoodDialog(QWidget *parent = nullptr);
    Food getNewFood() const;

private slots:
    void submit();

private:
    QLineEdit* nameEdit;
    QLineEdit* descriptionEdit;
    QLineEdit* priceEdit;
    QComboBox* categoryCombo;
    QLineEdit* imagePathEdit;
    QPushButton* submitBtn;
    Food createdFood;
    Food newFood;
};

#endif // ADD_FOOD_DIALOG_H





