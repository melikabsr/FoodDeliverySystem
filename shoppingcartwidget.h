#ifndef SHOPPINGCARTWIDGET_H
#define SHOPPINGCARTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QMap>
#include <QPair>
#include "Food.h"
class ClientNetwork;

class ShoppingCartWidget : public QWidget
{
    Q_OBJECT

public:
   // explicit ShoppingCartWidget(QWidget *parent = nullptr);
    explicit ShoppingCartWidget(ClientNetwork* network, const QString& username, QWidget* parent = nullptr);
    void addItem(const Food& food);
    void removeItem(int id);
    void refresh();

private:
    void updateDisplay();
    void loadCartItems();

    QVBoxLayout* layout;
    QLabel* totalLabel;
    QMap<int, QPair<Food, int>> items;


    ClientNetwork* network;
    QString username;
};

#endif // SHOPPINGCARTWIDGET_H
