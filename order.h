#ifndef ORDER_H
#define ORDER_H

#include <QString>
#include <QMap>
#include <QPair>
#include "Food.h"
#include "enums.h"

class Order
{
private:
    int id;
    QMap<int, QPair<Food, int>> items;
    OrderStatus status;
    double totalAmount;
    QString customerUsername;
    QString username;



public:
    Order();
    Order(int id, const QString& customerUsername);

    void addItem(const Food& food, int quantity);
    void calculateTotal();

    int getId() const;
    OrderStatus getStatus() const;
    void setStatus(OrderStatus newStatus);
    double getTotalAmount() const;
    QMap<int, QPair<Food, int>> getItems() const;
    QString getCustomerUsername() const;
};

#endif // ORDER_H
