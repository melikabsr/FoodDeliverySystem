#ifndef SHOPPINGCARTWIDGET_H
#define SHOPPINGCARTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QMap>
#include "Food.h"
#include <QPushButton>
#include "CustomerService.h"

class ShoppingCartWidget : public QWidget
{
    Q_OBJECT

public:

    explicit ShoppingCartWidget(QWidget *parent = nullptr);
    void addItem(const Food& food);
    void removeItem(int id);

private:
    QVBoxLayout* layout;
    QLabel* totalLabel;
    QMap<int, QPair<Food, int>> items;  // foodId → (Food, quantity)
    void updateDisplay();



    void loadCartItems();
    void refresh();
};

#endif // SHOPPINGCARTWIDGET_H

