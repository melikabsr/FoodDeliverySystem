#include "Order.h"

Order::Order(int id,
             const QString& customerUsername,
             const QList<QPair<Food, int>>& items,
             double totalPrice,
             const QDateTime& timestamp)
    : id(id),
    customerUsername(customerUsername),
    items(items),
    totalPrice(totalPrice),
    timestamp(timestamp),
    status(OrderStatus::PENDING)
{}

int Order::getId() const { return id; }
QString Order::getCustomerUsername() const { return customerUsername; }
QList<QPair<Food, int>> Order::getItems() const { return items; }
double Order::getTotalPrice() const { return totalPrice; }
QDateTime Order::getTimestamp() const { return timestamp; }
OrderStatus Order::getStatus() const { return status; }
void Order::setStatus(OrderStatus s) { status = s; }
