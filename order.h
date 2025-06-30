#ifndef ORDER_H
#define ORDER_H

#include <QString>
#include <QList>
#include <QDateTime>
#include "Food.h"

enum class OrderStatus {
    PENDING,
    PREPARING,
    READY,
    DELIVERED,
    CANCELLED
};

class Order
{
public:
    Order(int id,
          const QString& customerUsername,
          const QList<QPair<Food, int>>& items,
          double totalPrice,
          const QDateTime& timestamp = QDateTime::currentDateTime());

    int getId() const;
    QString getCustomerUsername() const;
    QList<QPair<Food, int>> getItems() const;
    double getTotalPrice() const;
    QDateTime getTimestamp() const;
    OrderStatus getStatus() const;

    void setStatus(OrderStatus status);

private:
    int id;
    QString customerUsername;
    QList<QPair<Food, int>> items;
    double totalPrice;
    QDateTime timestamp;
    OrderStatus status;
};

#endif // ORDER_H
