#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include <QObject>
#include <QVector>
#include "Order.h"

class OrderManager : public QObject
{
    Q_OBJECT

public:
    static OrderManager& instance();  // Singleton

    void addOrder(const Order& order);
    QVector<Order> getOrdersForCustomer(const QString& username) const;
    QVector<Order>& getAllOrders();
    Order* getOrderById(int id);

private:
    explicit OrderManager(QObject* parent = nullptr);
    QVector<Order> orders;
    int nextOrderId = 1;
};

#endif // ORDERMANAGER_H
